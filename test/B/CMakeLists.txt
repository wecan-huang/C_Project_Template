# 修改處 ###################################
	# 定義測試macro，例如MOCK_A，如果未使用條件式編譯，則可以使用set(T_MACRO "")，可視範圍自己和以下CMakeLists.txt
	set(T_MACRO MOCK_C)
	# 定義測試執行檔macro，可視範圍自己和以下CMakeLists.txt
	set(T_EXE test_B)
	# 定義測試執行檔名稱的macro，可視範圍自己和以下CMakeLists.txt
	set(T_NAME test_case_B)

	# 指定要生成的執行檔 //add_executable(<target> <source_files>...)
	add_executable(${T_EXE} 
		test_B.cpp 
		${SRC_DIR}/B/B.c 
		${SRC_DIR}/C/C.c
	)
# 修改處 ###################################


# 指定link的lib //target_link_libraries(<target> <libraries>...)
target_link_libraries(${T_EXE} gtest gtest_main pthread)

# 指定Preprocess的macro //target_compile_definitions(<target> [INTERFACE|PUBLIC|PRIVATE] <definitions>...)
target_compile_definitions(${T_EXE} PRIVATE ${T_MACRO})

# 添加測例到CMake測試框架，先前須先加入enable_testing() //add_test(NAME <test-name> COMMAND <command> [ARGS <arg1> <arg2> ...])
add_test(NAME ${T_NAME} COMMAND ${T_EXE})