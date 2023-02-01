include(FetchContent)
include(CMakePrintHelpers)

if(NOT TARGET hello_imgui)
    FetchContent_Declare(
        hello_imgui
        URL "ftp://yourhost/hello_imgui-master.zip"
        URL_HASH SHA512=f302aef9440ebaf4d621341db1592b74984f255ec90812f590890f631be1bed079c364084bab5f389421d23d87c0732ae60fef88c978ff1536d9a34b860c9366
        DOWNLOAD_NAME "hello_imgui-master.zip"
        DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/downloads/hello_imgui  
    )
    FetchContent_GetProperties(hello_imgui)

    if(NOT hello_imgui_POPULATED)
        #下载并解压hello_imgui源码包
        FetchContent_Populate(hello_imgui)

        set(TARGET_NAME "hello_imgui")
        set(SOURCE_DIR  "${hello_imgui_SOURCE_DIR}/src/hello_imgui")
        file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.h ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.c)
        add_library(${TARGET_NAME} ${SOURCE_FILES})
        target_include_directories(${TARGET_NAME} PUBLIC "${SOURCE_DIR}/../")
        target_include_directories(${TARGET_NAME} PRIVATE "${SOURCE_DIR}/")        
        set_target_properties(${TARGET_NAME} PROPERTIES 
            FOLDER "external"
        )

        if (need_fetch_make_available_glfw)
            set(GLFW_BUILD_EXAMPLES OFF)
            set(GLFW_BUILD_TESTS OFF)
            set(GLFW_BUILD_DOCS OFF)
            set(GLFW_INSTALL OFF)
            FetchContent_MakeAvailable(glfw)
            set_target_properties(glfw PROPERTIES
                FOLDER  "external"  
            )
            set_target_properties(update_mappings PROPERTIES
                FOLDER  "external"  
            )            
        endif()
        if (NOT TARGET glfw) # if glfw is not built as part of the whole build, find it
            find_package(glfw3 CONFIG REQUIRED)
        endif()

        #使用glfw+opengl3
        target_link_libraries(${TARGET_NAME} PUBLIC glfw imgui)
        target_sources(${TARGET_NAME} PRIVATE
            "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h"
            "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
            "${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.h"
            "${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
        )
        target_compile_definitions(${TARGET_NAME} PUBLIC HELLOIMGUI_USE_GLFW_OPENGL3)
        target_compile_definitions(${TARGET_NAME} PUBLIC HELLOIMGUI_USE_GLFW)
        target_compile_definitions(${TARGET_NAME} PUBLIC HELLOIMGUI_HAS_OPENGL)

        # OpenGL_Loaders
        set(GLAD_DIR "${hello_imgui_SOURCE_DIR}/external/OpenGL_Loaders/glad" CACHE INTERNAL "Directory of glad")   
        set(GLAD_FILES
            ${GLAD_DIR}/src/glad.c
            ${GLAD_DIR}/include/glad/glad.h
            ${GLAD_DIR}/include/KHR/khrplatform.h)
        add_library(glad ${GLAD_FILES})
        set_target_properties(glad PROPERTIES 
            FOLDER "external"
        )

        target_include_directories(glad PUBLIC SYSTEM ${GLAD_DIR}/include)
        if(WIN32)
            target_link_libraries(glad PUBLIC opengl32.lib)
        else()
            target_link_libraries(glad PUBLIC ${OPENGL_LIBRARIES})
        endif()
        target_compile_definitions(glad PUBLIC HELLOIMGUI_USE_GLAD)    

        target_compile_definitions(${TARGET_NAME} PUBLIC HELLOIMGUI_USE_GLAD IMGUI_IMPL_OPENGL_LOADER_GLAD)
        target_link_libraries(${TARGET_NAME} PUBLIC glad)
    endif()
endif()
