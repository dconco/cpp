# cmake_minimum_required(VERSION 3.15)
# project(MyCppApp)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Debug)

# # Add the executable from the src folder
# add_executable(MyCppApp src/main.cpp)

cmake_minimum_required(VERSION 3.10)
project(HotReloadApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable PDB generation for Debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG /OPT:NOREF /OPT:NOICF")

# Copy DLLs to output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Library with hot-reloadable code
add_library(app_logic SHARED
    src/logic/app_logic.cpp
    src/logic/app_logic.h
    src/logic/api.h
)

target_include_directories(app_logic PUBLIC src)

# Main application that loads the library
add_executable(app_main
    src/main/main.cpp
    src/main/loader.cpp
    src/main/loader.h
    src/logic/api.h
)

target_include_directories(app_main PUBLIC src)
target_link_libraries(app_main)