cmake_minimum_required(VERSION 3.25)
project(WorkBox)

# set(CMAKE_CXX_STANDARD 20)

# 设置vcpkg工具链文件，确保CMake能够使用vcpkg安装的库
set(CMAKE_TOOLCHAIN_FILE D:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# 添加可执行文件，包括所有相关的源文件
add_executable(WorkBox "main.cpp" "utils/common.cpp" "utils/SimpleDataFrame.cpp" "utils/headers/math_functions.h" "utils/math_functions.cpp")

find_package(NumCpp CONFIG REQUIRED)

target_link_libraries(WorkBox PRIVATE NumCpp::NumCpp)
