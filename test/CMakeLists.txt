# 定義C/C++標準的版本
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

# 使用子模組的CMakeLists.txt加入test case
add_subdirectory(A)
add_subdirectory(B)
add_subdirectory(C)