include(FetchContent)

FetchContent_Declare(
    glfw
    URL "ftp://yourhost/glfw-3.3.8.zip"
    URL_HASH SHA512=3661b74977d842e27df6f0b0ef50bdac9f34d6c9f44534af7cd357d1bcade5b3afc2e57e8a59e58f11d90966a59ff382e4faf0ca8e0825641d5f42b202df6c6d
    DOWNLOAD_NAME "glfw-3.3.8.zip"
    DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/downloads/glfw
)
#让hello_imgui来添加glfw
set(need_fetch_make_available_glfw ON  CACHE INTERNAL "glfw can be available") 
