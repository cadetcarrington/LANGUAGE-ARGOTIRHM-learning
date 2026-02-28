#!/bin/bash

# 定义 .gitignore 文件位置
GITIGNORE=".gitignore"
touch "$GITIGNORE"

echo "🔍 开始递归扫描子目录中的二进制文件..."

# 使用 find 递归查找所有文件 (-type f)
# 排除 .git 目录避免干扰
find . -type f -not -path '*/.*' | while read -r file; do
    
    # 获取文件的 MIME 类型
    mimetype=$(file -b --mime-type "$file")
    
    # 判断是否为可执行二进制文件
    if [[ "$mimetype" == "application/x-executable" || "$mimetype" == "application/x-sharedlib" || "$mimetype" == "application/x-pie-executable" ]]; then
        
        # 移除路径开头的 ./ 方便 git 识别
        clean_path="${file#./}"
        
        # 检查是否已经在 .gitignore 中，不在则追加
        if ! grep -qx "$clean_path" "$GITIGNORE"; then
            echo "$clean_path" >> "$GITIGNORE"
            echo "✅ 已添加: $clean_path"
        fi
    fi
done

echo "✨ 扫描完成！"