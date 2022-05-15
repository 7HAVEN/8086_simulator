cmake_minimum_required(VERSION 3.21)
project(simulator)

set(CMAKE_CXX_STANDARD 14)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified : Build type set to reset by default")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
    set(CMAKE_CXX_FLAGS - "-g -O0")
endif(CMAKE_BUILD_TYPE EQUAL "Debug")

if(CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS "-O2")
endif(CMAKE_BUILD_TYPE EQUAL "Release")

file(GLOB_RECURSE simulator_src src/*.cpp)

add_executable(simulator ${simulator_src})
include_directories(simulator src/include)

#glfw

add_subdirectory(externals/glfw)

#imgui
add_library(
    imgui
    externals/imgui/imconfig.h
    externals/imgui/imgui_demo.cpp
    externals/imgui/imgui_draw.cpp
    externals/imgui/imgui_internal.h
    externals/imgui/imgui_tables.cpp
    externals/imgui/imgui_widgets.cpp
    externals/imgui/imgui.cpp
    externals/imgui/imgui.h
    externals/imgui/imstb_rectpack.h
    externals/imgui/imstb_textedit.h
    externals/imgui/imstb_truetype.h
    externals/imgui/backends/imgui_impl_glfw.h
    externals/imgui/backends/imgui_impl_glfw.cpp
    externals/imgui/backends/imgui_impl_opengl3.h
    externals/imgui/backends/imgui_impl_opengl3.cpp
    externals/imgui/backends/imgui_impl_opengl3_loader.h

)
include_directories(imgui externals/imgui/  externals/imgui/backends/)

target_link_libraries(imgui glfw )
target_link_libraries(simulator glfw imgui opengl32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)