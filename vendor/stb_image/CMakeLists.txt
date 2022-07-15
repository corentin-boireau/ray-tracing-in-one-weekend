message(STATUS "Fetching stb_image...")

FetchContent_MakeAvailable(stb_image)
target_include_directories(raytracer PRIVATE ${stb_image_SOURCE_DIR})