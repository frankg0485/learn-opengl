cmake_minimum_required(VERSION 3.10)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(main src/main.cpp src/glad.c src/Shader.cpp)

#include_directories(/usr/local/include)
target_include_directories(main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
#link_directories(/usr/local/lib)

target_link_libraries(main 
    glfw
)
