#!/usr/bin/env bash
set -u

GITIGNORE=".gitignore"
SCRIPT_NAME="$(basename "$0")"

DRY_RUN=0
INCLUDE_OCTET_STREAM=0
SCAN_EXECUTABLE=0
BATCH_SIZE=200

usage() {
    cat <<EOF
用法:
  $SCRIPT_NAME [选项]

选项:
  --dry-run                只显示将要添加的内容，不修改 .gitignore
  --include-octet-stream   也把 application/octet-stream 当作二进制文件处理
  --scan-executable        扫描所有带可执行权限的文件，而不只是常见二进制后缀
  -h, --help               显示帮助

推荐:
  先运行:
    ./$SCRIPT_NAME --dry-run

确认没问题后:
    ./$SCRIPT_NAME
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --dry-run)
            DRY_RUN=1
            ;;
        --include-octet-stream)
            INCLUDE_OCTET_STREAM=1
            ;;
        --scan-executable)
            SCAN_EXECUTABLE=1
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "❌ 未知参数: $1"
            usage
            exit 1
            ;;
    esac
    shift
done

tmpdir="$(mktemp -d 2>/dev/null || mktemp -d -t ignore-binaries)"
existing_entries="$tmpdir/existing_entries"
new_entries="$tmpdir/new_entries"
mime_output="$tmpdir/mime_output"

cleanup() {
    rm -rf "$tmpdir"
}
trap cleanup EXIT

: > "$existing_entries"
: > "$new_entries"

if [[ -f "$GITIGNORE" ]]; then
    awk '
        NF == 0 { next }
        $0 ~ /^[[:space:]]*#/ { next }
        { print }
    ' "$GITIGNORE" > "$existing_entries"
elif [[ "$DRY_RUN" -eq 0 ]]; then
    touch -- "$GITIGNORE"
fi

echo "🔍 开始扫描当前目录及子目录中的二进制文件..."

if [[ "$DRY_RUN" -eq 1 ]]; then
    echo "🧪 当前为 dry-run 模式，不会修改 $GITIGNORE"
fi

is_candidate_name() {
    case "$1" in
        *.o|*.a|*.so|*.so.*|*.out|*.bin|*.exe|*.dll|*.dylib|\
        *.class|*.pyc|*.pyo|*.mod|*.gch|*.pcm|*.dSYM)
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}

is_binary_mime() {
    case "$1" in
        application/x-executable|\
        application/x-sharedlib|\
        application/x-pie-executable|\
        application/x-object|\
        application/x-archive|\
        application/x-mach-binary|\
        application/x-dosexec|\
        application/x-msdownload|\
        application/vnd.microsoft.portable-executable|\
        application/java-vm|\
        application/x-bytecode.python|\
        application/x-coredump)
            return 0
            ;;
        application/octet-stream)
            [[ "$INCLUDE_OCTET_STREAM" -eq 1 ]]
            return
            ;;
        *)
            return 1
            ;;
    esac
}

escape_gitignore_path() {
    local p="$1"

    p="${p//\\/\\\\}"
    p="${p//\*/\\*}"
    p="${p//\?/\\?}"
    p="${p//\[/\\[}"
    p="${p//\]/\\]}"

    printf '/%s\n' "$p"
}

already_listed() {
    local clean_path="$1"
    local entry="$2"

    grep -Fxq -- "$entry" "$existing_entries" && return 0
    grep -Fxq -- "$clean_path" "$existing_entries" && return 0
    grep -Fxq -- "$entry" "$new_entries" && return 0
    grep -Fxq -- "$clean_path" "$new_entries" && return 0

    return 1
}

is_already_ignored_by_git() {
    local clean_path="$1"

    if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        git check-ignore -q -- "$clean_path" 2>/dev/null
        return $?
    fi

    return 1
}

scanned=0
candidates=0
binary_found=0
added=0
skipped=0
weird_skipped=0
files=()

process_candidate_with_mime() {
    local file="$1"
    local mimetype="$2"
    local clean_path
    local entry

    clean_path="${file#./}"

    if ! is_binary_mime "$mimetype"; then
        return 0
    fi

    ((binary_found++))

    case "$clean_path" in
        *$'\n'*)
            echo "⚠️ 跳过包含换行符的路径: $clean_path"
            ((weird_skipped++))
            return 0
            ;;
    esac

    entry="$(escape_gitignore_path "$clean_path")"

    if already_listed "$clean_path" "$entry"; then
        ((skipped++))
        return 0
    fi

    if is_already_ignored_by_git "$clean_path"; then
        ((skipped++))
        return 0
    fi

    printf '%s\n' "$entry" >> "$new_entries"
    ((added++))

    if [[ "$DRY_RUN" -eq 1 ]]; then
        echo "🟡 将添加: $entry"
    else
        echo "✅ 已准备添加: $entry"
    fi
}

flush_candidates() {
    local i
    local mimetype

    [[ "${#files[@]}" -eq 0 ]] && return 0

    : > "$mime_output"

    if ! file --mime-type -b -- "${files[@]}" > "$mime_output" 2>/dev/null; then
        echo "⚠️ file 命令处理部分文件失败，跳过这一批。"
        files=()
        return 0
    fi

    i=0
    while IFS= read -r mimetype || [[ -n "$mimetype" ]]; do
        if [[ "$i" -lt "${#files[@]}" ]]; then
            process_candidate_with_mime "${files[$i]}" "$mimetype"
        fi
        i=$((i + 1))
    done < "$mime_output"

    files=()
}

while IFS= read -r -d '' file; do
    ((scanned++))

    clean_path="${file#./}"

    case "$clean_path" in
        "$GITIGNORE"|"$SCRIPT_NAME"|"$SCRIPT_NAME".bak.*)
            continue
            ;;
    esac

    if is_candidate_name "$clean_path"; then
        files+=("$file")
        ((candidates++))
    elif [[ "$SCAN_EXECUTABLE" -eq 1 && -x "$file" ]]; then
        files+=("$file")
        ((candidates++))
    else
        continue
    fi

    if [[ "${#files[@]}" -ge "$BATCH_SIZE" ]]; then
        flush_candidates
    fi
done < <(
    find . \
        \( -type d \( \
            -name '.git' -o \
            -name 'build' -o \
            -name 'build-*' -o \
            -name 'cmake-build-*' -o \
            -name 'dep' -o \
            -name 'deps' -o \
            -name 'extern' -o \
            -name 'external' -o \
            -name 'node_modules' -o \
            -name '.venv' -o \
            -name 'venv' -o \
            -name '__pycache__' \
        \) -prune \) -o \
        -type f -print0
)

flush_candidates

if [[ "$added" -gt 0 && "$DRY_RUN" -eq 0 ]]; then
    {
        echo ""
        echo "# Binary files added by $SCRIPT_NAME on $(date '+%Y-%m-%d')"
        cat "$new_entries"
    } >> "$GITIGNORE"
fi

echo "✨ 扫描完成！"
echo "   已扫描文件: $scanned"
echo "   候选文件:   $candidates"
echo "   二进制文件: $binary_found"
echo "   新增记录:   $added"
echo "   跳过记录:   $skipped"
echo "   异常跳过:   $weird_skipped"

if [[ "$DRY_RUN" -eq 1 ]]; then
    echo ""
    echo "🧪 dry-run 模式未修改 $GITIGNORE。确认无误后运行："
    echo "   ./$SCRIPT_NAME"
fi