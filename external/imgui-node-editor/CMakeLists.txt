include(FetchContent)
include(CMakePrintHelpers)

if(NOT TARGET imgui_node_editor)
    FetchContent_Declare(
        imgui_node_editor
        URL "ftp://yourhost/imgui-node-editor-master.zip"
        URL_HASH SHA512=3b9260fc9d0f4369ff5854635cd24f55080588a4ce7398a90501f0456e0298494b103b2b96bba89b79ed6eeaa388fcd86d6254f11ccbdd1da8820322b8542fd8
        DOWNLOAD_NAME "imgui-node-editor-master.zip"
        DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/downloads/imgui-node-editor  
    )
    FetchContent_GetProperties(imgui_node_editor)

    if(NOT imgui_node_editor_POPULATED)
        #下载并解压imgui-node-editor源码包
        FetchContent_Populate(imgui_node_editor)

        set(TARGET_NAME "imgui_node_editor")
        set(SOURCE_DIR  ${imgui_node_editor_SOURCE_DIR})
        file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.h ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.inl)
        add_library(${TARGET_NAME} ${SOURCE_FILES})
        target_include_directories(${TARGET_NAME} PUBLIC ${SOURCE_DIR})
        set_target_properties(${TARGET_NAME} PROPERTIES 
            FOLDER "external"
        )
        target_link_libraries(${TARGET_NAME} PUBLIC imgui)
    endif()
endif()
