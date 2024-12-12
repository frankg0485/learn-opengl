cmake_minimum_required(VERSION 3.10)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(main src/main.cpp src/glad.c)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

target_link_libraries(main 
    glfw
)
