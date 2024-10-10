#!/bin/bash

# 獲取當前腳本的目錄
current_dir=$(dirname "$(realpath "$0")")

# 向上遞歸查找 README.md 來確定專案根目錄
while [[ "$current_dir" != "/" ]]; do
    if [[ -f "$current_dir/README.md" ]]; then
        #echo "專案根目錄: $current_dir"
		project_root="$current_dir"
		return
    fi
    current_dir=$(dirname "$current_dir")  # 向上遞歸
done

echo "找不到專案根目錄！"
