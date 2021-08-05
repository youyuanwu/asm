cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

project(asm CXX)

# target_include_directories(
#     asm
#     INTERFACE
#     "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
# )

include_directories(${asm_SOURCE_DIR}/include)
add_library(asm ${asm_SOURCE_DIR}/src/asm.cpp)

#add_subdirectory(src)

enable_testing()
add_subdirectory(test)

