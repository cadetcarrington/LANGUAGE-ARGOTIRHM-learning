#!/usr/bin/env bash
set -u

GITIGNORE=".gitignore"
SCRIPT_NAME="$(basename "$0")"

DRY_RUN=0
INCLUDE_OCTET_STREAM=0
SCAN_EXECUTABLE=0
SCAN_ALL=0
BATCH_SIZE=200

usage() {
    cat <<EOF
用法:
  $SCRIPT_NAME [选项]

选项:
  --dry-run                只显示将要添加的内容，不修改 .gitignore
  --scan-all               🔥 无视后缀名和权限，全量扫描（配合并行化速度极快）
  --scan-executable        扫描所有带可执行权限的文件
  --include-octet-stream   也把 application/octet-stream 当作二进制文件处理
  -h, --help               显示帮助
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --dry-run) DRY_RUN=1 ;;
        --scan-all) SCAN_ALL=1 ;;
        --include-octet-stream) INCLUDE_OCTET_STREAM=1 ;;
        --scan-executable) SCAN_EXECUTABLE=1 ;;
        -h|--help) usage; exit 0 ;;
        *) echo "❌ 未知参数: $1"; usage; exit 1 ;;
    esac
    shift
done

# 获取 CPU 核心数用于并行 (Linux 使用 nproc, macOS 使用 sysctl)
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

if [[ "$SCAN_ALL" -eq 1 ]]; then
    echo "🔍 [全量并行模式] 开启 $CORES 线程读取底层文件头..."
else
    echo "🔍 [并行模式] 开启 $CORES 线程扫描二进制文件..."
fi

if [[ "$DRY_RUN" -eq 1 ]]; then echo "🧪 当前为 dry-run 模式，不会修改 $GITIGNORE"; fi

# ==========================================
# 🛠️ 构建多线程 Worker 脚本
# ==========================================
cat << 'EOF' > "$worker_script"
#!/usr/bin/env bash
# 接收 xargs 传来的文件列表
files=("$@")
[[ ${#files[@]} -eq 0 ]] && exit 0

valid_files=()
for file in "${files[@]}"; do
    clean_path="${file#./}"
    case "$clean_path" in
        "$GITIGNORE_NAME"|"$SCRIPT_NAME"|"$SCRIPT_NAME".bak.*) continue ;;
    esac

    if [[ "$SCAN_ALL" -eq 1 ]]; then
        valid_files+=("$file")
    else
        is_candidate=0
        case "$clean_path" in
            *.o|*.a|*.so|*.so.*|*.out|*.bin|*.exe|*.dll|*.dylib|*.class|*.pyc|*.pyo|*.mod|*.gch|*.pcm|*.dSYM|*.wasm)
                is_candidate=1 ;;
        esac
        if [[ "$is_candidate" -eq 1 ]]; then
            valid_files+=("$file")
        elif [[ "$SCAN_EXECUTABLE" -eq 1 && -x "$file" ]]; then
            valid_files+=("$file")
        fi
    fi
done

[[ ${#valid_files[@]} -eq 0 ]] && exit 0

# 多线程安全输出文件（按进程 PID 命名，避免抢占冲突）
output_file="$WORKER_RESULTS_DIR/result_$\$.txt"

# 批量执行 file
mime_output=$(file --mime-type -b -- "${valid_files[@]}" 2>/dev/null)
[[ -z "$mime_output" ]] && exit 0

# 解析 file 输出并判定
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
            # 过滤换行符
            case "$clean_path" in
                *$'\n'*) ;;
                *) echo "$clean_path" >> "$output_file" ;;
            esac
        fi
    fi
    i=$((i+1))
done
EOF
chmod +x "$worker_script"

# 导出环境变量供 Worker 使用
export GITIGNORE_NAME="$GITIGNORE"
export SCRIPT_NAME
export SCAN_ALL
export SCAN_EXECUTABLE
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
# ✨ 批量去重与过滤 (维持极速不变)
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