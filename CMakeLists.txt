cmake_minimum_required(VERSION 3.20)

project(Ray_Tracing_in_One_Weekend
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")


add_subdirectory(src)
add_subdirectory(vendor)