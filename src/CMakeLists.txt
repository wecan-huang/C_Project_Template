# 修改處 ###################################
	# 定義執行檔macro，可視範圍自己和以下CMakeLists.txt
	set(MAIN_EXE main)
# 修改處 ###################################

# 指定要生成的執行檔 //add_executable(<target> <source_files>...)
add_executable(${MAIN_EXE} ${SRC_FILES})