include(FetchContent)

FetchContent_Declare(stb_image
    GIT_REPOSITORY "https://github.com/nothings/stb"
    GIT_TAG GIT_TAG af1a5bc352164740c1cc1354942b1c6b72eacb8a
)

add_subdirectory(stb_image)