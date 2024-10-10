# cmake最低版本需求
cmake_minimum_required(VERSION 3.10)

# 預設產生src執行檔
option(UNIT_TEST "Generate unit test?" OFF)

# 基於選項創建不同執行檔
if(UNIT_TEST)
	message(STATUS "Generate unit test project...")

	# 定義專案類型 //project(<project-name> [LANGUAGES <language-names>...] [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]])
	project(MyTestProject C CXX)

	# 設定path相關 //set(<variable> <value>... [CACHE <type> <docstring> [FORCE]])
	set(COMPILER_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
	set(PREPROCESS_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
	set(EXECUTABLE_OUTPUT_PATH ${COMPILER_OUTPUT_PATH}/bin/test)
	set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
	set(TEST_CASE_DIR ${CMAKE_SOURCE_DIR}/test)
	set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

	# 指定header搜尋路徑(default: include往前放，將優先被查找) //include_directories([AFTER|BEFORE] [SYSTEM] <dir1> [<dir2> ...])
	include_directories(${SRC_DIR})
	include_directories(${THIRD_PARTY_DIR}/gtest/include)
	include_directories(${THIRD_PARTY_DIR}/fff)

	# 設定gtest相關
	set(GTEST_INCLUDE_DIR ${THIRD_PARTY_DIR}/gtest/googletest/include)
	set(GTEST_LIBRARY ${THIRD_PARTY_DIR}/gtest/build/lib/libgtest.a)
	set(GTEST_MAIN_LIBRARY ${THIRD_PARTY_DIR}/gtest/build/lib/libgtest_main.a)

	# find_package(GTest REQUIRED) //find_package(<PackageName> [version] [REQUIRED] [QUIET] [MODULE] [EXACT] [NO_MODULE] [CONFIG] [NAMES name1 [name2 ...]] [COMPONENTS [components ...]] [OPTIONAL_COMPONENTS [components ...]] [NO_POLICY_SCOPE])
	# include_directories(${GTEST_INCLUDE_DIR})
	# 使用子模組的CMakeLists.txt加入gtest lib //add_subdirectory(<source_dir> [binary_dir] [EXCLUDE_FROM_ALL])
	add_subdirectory(${THIRD_PARTY_DIR}/gtest)

	# 使用子模組的CMakeLists.txt加入fff lib
	add_subdirectory(${THIRD_PARTY_DIR}/fff)

	# 啟動測試功能 //enable_testing()
	enable_testing()

	# 使用子模組的CMakeLists.txt加入test suite
	add_subdirectory(${TEST_CASE_DIR})
else()
	message(STATUS "Generate main project...")

	# 定義專案類型
	project(MyProject C)

	# 設定path相關
	set(COMPILER_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
	set(PREPROCESS_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
	set(EXECUTABLE_OUTPUT_PATH ${COMPILER_OUTPUT_PATH}/bin)
	set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

	# 指定header搜尋路徑
	include_directories(${SRC_DIR})

	# 查找該目錄底下.c檔
	#file(GLOB SRC_FILES "${SRC_DIR}/*.c")
	# 查找該目錄與其所有子目錄.c檔
	file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.c")

	# 使用子模組的CMakeLists.txt加入main code
	add_subdirectory(${SRC_DIR})
endif()