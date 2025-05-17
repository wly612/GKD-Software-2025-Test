# 最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(test VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加头文件搜索路径
include_directories(/home/wly/text/GKD-Software-2025-Test/test/include)

# 收集源文件
file(GLOB_RECURSE SOURCES "/home/wly/text/GKD-Software-2025-Test/test/src/*.cpp")

# 添加可执行文件
add_executable(myapp ${SOURCES})

# 安装目标
find_package(OpenCV REQUIRED)

# 添加头文件目录
include_directories(${OpenCV_INCLUDE_DIRS} pthread)

# 链接 OpenCV 库
target_link_libraries(myapp ${OpenCV_LIBS})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g")






