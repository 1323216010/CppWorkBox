cmake_minimum_required(VERSION 3.25)
project(WorkBox)

# 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 20)

# 设置vcpkg工具链文件，确保CMake能够使用vcpkg安装的库
set(CMAKE_TOOLCHAIN_FILE D:/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

# 定义源文件列表（如果文件多，可以考虑使用 FILE(GLOB ...)）
set(SOURCE_FILES
    "main.cpp"
    "utils/common.cpp"
    "utils/SimpleDataFrame.cpp"
    "utils/headers/math_functions.h"
    "utils/math_functions.cpp"
)

# 添加可执行文件
add_executable(WorkBox ${SOURCE_FILES})

# 查找 NumCpp 库
find_package(NumCpp CONFIG REQUIRED)

# 链接 NumCpp 库
target_link_libraries(WorkBox PRIVATE NumCpp::NumCpp)
