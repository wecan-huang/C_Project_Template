# 修改處 ###################################
	# 定義測試執行檔macro，可視範圍自己和以下CMakeLists.txt
	set(T_EXE test_C)
	# 定義測試執行檔名稱的macro，可視範圍自己和以下CMakeLists.txt
	set(T_NAME test_case_C)

	# 指定要生成的執行檔 //add_executable(<target> <source_files>...)
	add_executable(${T_EXE} 
		# 測試案例 
		test_C.cpp
		# 測試對象 
		${SRC_DIR}/C/C.c
		# 不要加入要被mock對象, 例如: 對A.c測試，不可以加入${SRC_DIR}/B/B.c 
	)
# 修改處 ###################################


# 指定link的lib //target_link_libraries(<target> <libraries>...)
target_link_libraries(${T_EXE} gtest gtest_main pthread)

# 添加測例到CMake測試框架，先前須先加入enable_testing() //add_test(NAME <test-name> COMMAND <command> [ARGS <arg1> <arg2> ...])
add_test(NAME ${T_NAME} COMMAND ${T_EXE})