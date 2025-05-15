cmake_minimum_required(VERSION 3.15)
project(MyCppApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Add the executable from the src folder
add_executable(MyCppApp src/main.cpp)