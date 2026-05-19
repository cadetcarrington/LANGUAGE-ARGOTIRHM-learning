#!/usr/bin/env bash
set -u

GITIGNORE=".gitignore"
SCRIPT_NAME="$(basename "$0")"

DRY_RUN=0
INCLUDE_OCTET_STREAM=0
BATCH_SIZE=200

usage() {
    cat <<EOF
用法:
  $SCRIPT_NAME [选项]

说明:
  本脚本采用全量扫描模式，无视文件后缀名和权限，直接通过读取所有文件的底层
  文件头 (Magic Number) 来精准揪出所有二进制程序文件，并支持多核并行加速。

选项:
  --dry-run                只显示将要添加的内容，不修改 .gitignore
  --include-octet-stream   也把 application/octet-stream 当作二进制文件处理
  -h, --help               显示帮助
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --dry-run) DRY_RUN=1 ;;
        --include-octet-stream) INCLUDE_OCTET_STREAM=1 ;;
        -h|--help) usage; exit 0 ;;
        *) echo "❌ 未知参数: $1"; usage; exit 1 ;;
    esac
    shift
done

# 获取 CPU 核心数用于并行加速
if command -v nproc >/dev/null 2>&1; then
    CORES=$(nproc)
elif command -v sysctl >/dev/null 2>&1; then
    CORES=$(sysctl -n hw.ncpu)
else
    CORES=4
fi

tmpdir="$(mktemp -d 2>/dev/null || mktemp -d -t ignore-binaries)"
existing_entries="$tmpdir/existing_entries"
new_entries="$tmpdir/new_entries"
candidates_paths="$tmpdir/candidates_paths.txt"
worker_script="$tmpdir/worker.sh"
worker_results_dir="$tmpdir/results"

mkdir -p "$worker_results_dir"

cleanup() {
    rm -rf "$tmpdir"
}
trap cleanup EXIT

: > "$existing_entries"
: > "$new_entries"
: > "$candidates_paths"

if [[ -f "$GITIGNORE" ]]; then
    awk 'NF == 0 { next } $0 ~ /^[[:space:]]*#/ { next } { print }' "$GITIGNORE" > "$existing_entries"
elif [[ "$DRY_RUN" -eq 0 ]]; then
    touch -- "$GITIGNORE"
fi

echo "🔍 [全量并行模式] 开启 $CORES 线程读取底层文件头..."
if [[ "$DRY_RUN" -eq 1 ]]; then echo "🧪 当前为 dry-run 模式，不会修改 $GITIGNORE"; fi

# ==========================================
# 🛠️ 构建多线程 Worker 脚本 (纯净全量模式)
# ==========================================
cat << 'EOF' > "$worker_script"
#!/usr/bin/env bash
files=("$@")
[[ ${#files[@]} -eq 0 ]] && exit 0

valid_files=()
for file in "${files[@]}"; do
    clean_path="${file#./}"
    # 仅跳过脚本自身和 .gitignore，其余全部送检
    case "$clean_path" in
        "$GITIGNORE_NAME"|"$SCRIPT_NAME"|"$SCRIPT_NAME".bak.*) continue ;;
        *) valid_files+=("$file") ;;
    esac
done

[[ ${#valid_files[@]} -eq 0 ]] && exit 0

output_file="$WORKER_RESULTS_DIR/result_$\$.txt"

# 批量执行 file 命令
mime_output=$(file --mime-type -b -- "${valid_files[@]}" 2>/dev/null)
[[ -z "$mime_output" ]] && exit 0

# 解析输出结果
i=0
echo "$mime_output" | while IFS= read -r mimetype; do
    if [[ "$i" -lt "${#valid_files[@]}" ]]; then
        clean_path="${valid_files[$i]#./}"
        is_bin=0
        case "$mimetype" in
            application/x-executable|application/x-sharedlib|application/x-pie-executable|\
            application/x-object|application/x-archive|application/x-mach-binary|\
            application/x-dosexec|application/x-msdownload|application/vnd.microsoft.portable-executable|\
            application/wasm|application/java-vm|application/x-bytecode.python|application/x-coredump)
                is_bin=1 ;;
            application/octet-stream)
                [[ "$INCLUDE_OCTET_STREAM" -eq 1 ]] && is_bin=1 ;;
        esac

        if [[ "$is_bin" -eq 1 ]]; then
            case "$clean_path" in
                *$'\n'*) ;; # 跳过包含换行符的奇葩路径
                *) echo "$clean_path" >> "$output_file" ;;
            esac
        fi
    fi
    i=$((i+1))
done
EOF
chmod +x "$worker_script"

export GITIGNORE_NAME="$GITIGNORE"
export SCRIPT_NAME
export INCLUDE_OCTET_STREAM
export WORKER_RESULTS_DIR="$worker_results_dir"

# ==========================================
# 🚀 启动并行处理管道
# ==========================================
find . \
    \( -type d \( \
        -name '.git' -o -name 'build' -o -name 'build-*' -o -name 'cmake-build-*' -o \
        -name 'dep' -o -name 'deps' -o -name 'extern' -o -name 'external' -o \
        -name 'node_modules' -o -name '.venv' -o -name 'venv' -o -name '__pycache__' \
    \) -prune \) -o \
    -type f -print0 | xargs -0 -P "$CORES" -n "$BATCH_SIZE" "$worker_script"

# 合并所有线程的处理结果
find "$worker_results_dir" -type f -name 'result_*.txt' -exec cat {} + > "$candidates_paths"

# ==========================================
# ✨ 批量去重与过滤
# ==========================================
binary_found=$(wc -l < "$candidates_paths" | tr -d ' ')
added=0
skipped=0

escape_gitignore_path() {
    local p="$1"
    p="${p//\\/\\\\}"; p="${p//\*/\\*}"; p="${p//\?/\\?}"; p="${p//\[/\\[}"; p="${p//\]/\\]}"
    printf '/%s\n' "$p"
}

if [[ -s "$candidates_paths" ]]; then
    step1="$tmpdir/step1.txt"
    step2="$tmpdir/step2.txt"
    step3="$tmpdir/step3.txt"
    entries_raw="$tmpdir/entries_raw.txt"
    git_ignored="$tmpdir/git_ignored.txt"

    : > "$git_ignored"
    if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        git -c core.quotePath=false check-ignore --stdin < "$candidates_paths" > "$git_ignored" 2>/dev/null || true
    fi

    if [[ -s "$git_ignored" ]]; then
        grep -v -F -x -f "$git_ignored" "$candidates_paths" > "$step1" || true
    else
        cp "$candidates_paths" "$step1"
    fi

    if [[ -s "$existing_entries" ]]; then
        grep -v -F -x -f "$existing_entries" "$step1" > "$step2" || true
    else
        cp "$step1" "$step2"
    fi

    : > "$entries_raw"
    while IFS= read -r cp_line; do
        escape_gitignore_path "$cp_line" >> "$entries_raw"
    done < "$step2"

    if [[ -s "$existing_entries" ]]; then
        grep -v -F -x -f "$existing_entries" "$entries_raw" > "$step3" || true
    else
        cp "$entries_raw" "$step3"
    fi

    awk '!seen[$0]++' "$step3" > "$new_entries"

    while IFS= read -r entry; do
        ((added++))
        if [[ "$DRY_RUN" -eq 1 ]]; then echo "🟡 将添加: $entry"
        else echo "✅ 已准备添加: $entry"
        fi
    done < "$new_entries"

    skipped=$((binary_found - added))
fi

if [[ "$added" -gt 0 && "$DRY_RUN" -eq 0 ]]; then
    {
        echo ""
        echo "# Binary files added by $SCRIPT_NAME on $(date '+%Y-%m-%d')"
        cat "$new_entries"
    } >> "$GITIGNORE"
fi

echo "✨ 扫描完成！(使用了 $CORES 个 CPU 核心)"
echo "   识别出二进制: $binary_found"
echo "   新增忽略记录: $added"
echo "   跳过(已存在): $skipped"