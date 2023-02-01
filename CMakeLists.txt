cmake_minimum_required(VERSION 3.12)

project(imgui_template)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

#生成Visual Studio工程时使用文件夹组织结构
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#MSVC情况下开启并行构建
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

#设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#设置动态链接库输出目录
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
endif()
#设置库输出目录
# if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
#     set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
# endif()

add_subdirectory(external)

add_executable(hello_world hello_world.cpp)

target_link_options(hello_world PRIVATE /SUBSYSTEM:WINDOWS)
target_link_libraries(hello_world PRIVATE hello_imgui)

#部署资源文件 
add_custom_command(TARGET hello_world POST_BUILD 
    ##复制数据
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets  $<TARGET_FILE_DIR:hello_world>/assets
)

add_subdirectory(examples)
