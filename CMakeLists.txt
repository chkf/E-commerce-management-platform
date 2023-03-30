# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.5)
# 项目信息
project(Ecmp)
# 设置输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
#添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/inc)
#查找Sources文件夹下源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
#编译
add_executable(Ecmp ${DIR_SRCS})