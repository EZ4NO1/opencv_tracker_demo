# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
set(OpenCV_DIR C:\\Program\ Files\\opencv4_5\\x64\\vc16\\lib)
find_package(OpenCV REQUIRED)
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (CMakeProject1 "CMakeProject1.cpp" )
message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBS})
message(${OpenCV_LIBS})
target_include_directories(CMakeProject1 PUBLIC ${OpenCV_INCLUDE_DIRS})
#link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(CMakeProject1 PUBLIC ${OpenCV_LIBS})

# TODO: 如有需要，请添加测试并安装目标。
