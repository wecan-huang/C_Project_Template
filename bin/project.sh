#!/bin/bash

# 使用source呼叫子腳本可以取得子腳本變數，確保bash與bin在同一層
source ./bash/find_project_root.sh

# 若專案根目錄找不到，則顯示錯誤訊息並結束程式
if [ ! -d "$project_root" ]; then
    echo "Error: 找不到根目錄."
    exit 1
fi

#echo "專案根目錄: $project_root"

# 檢查是否有參數
if [[ $# -eq 0 ]]; then
    echo "請提供參數！可用參數: run_all, run_project, run_all_test, run_file <filename>, help"
    exit 1
fi

bin_rep_path="$project_root/build/bin"
project_bin_path="$bin_rep_path"
test_bin_path="$bin_rep_path/test"

# 根據第一個參數執行對應行為
case $1 in
    run_all)
        echo "正在執行當前目錄下的所有 .exe 文件..."
        for exe_file in ${project_bin_path}/*.exe; do
            if [[ -x "$exe_file" ]]; then
                echo "執行: $exe_file"
                "$exe_file"
            else
                echo "$exe_file 不是可執行文件，跳過"
            fi
        done

        for exe_file in ${test_bin_path}/*.exe; do
            if [[ -x "$exe_file" ]]; then
                echo "執行: $exe_file"
                "$exe_file"
            else
                echo "$exe_file 不是可執行文件，跳過"
            fi
        done
        ;;

    run_project)
        echo "正在執行當前專案的 .exe 文件..."
        for exe_file in ${project_bin_path}/*.exe; do
            if [[ -x "$exe_file" ]]; then
                echo "執行: $exe_file"
                "$exe_file"
            else
                echo "$exe_file 不是可執行文件，跳過"
            fi
        done
        ;;

    run_all_test)
        echo "正在執行測試(test)目錄下的所有 .exe 文件..."
        for exe_file in ${test_bin_path}/*.exe; do
            if [[ -x "$exe_file" ]]; then
                echo "執行: $exe_file"
                "$exe_file"
            else
                echo "$exe_file 不是可執行文件，跳過"
            fi
        done
        ;;

    run_file)
        if [[ -z $2 ]]; then
            echo "請提供要執行的 .exe 文件名！"
            exit 1
        fi
        
        if [[ -x $2 ]]; then
            echo "正在執行文件: $2"
            "$2"
        else
            echo "$2 不是可執行文件，或找不到該文件！"
        fi
        ;;
    
    help)
        echo "可用參數說明："
        echo "run_all               - 執行當前目錄下的所有 .exe 文件"
        echo "run_project           - 執行當前專案的 .exe 文件"
        echo "run_all_test          - 執行測試(test)目錄下的所有 .exe 文件"
        echo "run_file <filename>   - 執行指定的 .exe 文件"
        echo "help                  - 顯示此幫助信息"
        ;;
    
    *)
        echo "未知的參數！請使用 'help' 來查看可用的參數。"
        exit 1
        ;;
esac

exit 0