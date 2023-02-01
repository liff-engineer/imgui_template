file(GLOB examples CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(example ${examples})
    #message(STATUS "${example}")
    get_filename_component(file ${example} NAME_WLE)
    #message(STATUS "${file}")

    # 资源文件的处理
    set(ApplicationIcon ${CMAKE_CURRENT_SOURCE_DIR}/Icon.ico)
    file(TO_NATIVE_PATH "${ApplicationIcon}" ApplicationIcon)
    string(REPLACE "\\" "\\\\" ApplicationIcon "${ApplicationIcon}")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc
    )
    source_group("resources" FILES ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc)
    
    # 实例定义
    set(target_name ${file})
    add_executable(${target_name} ${example} ${CMAKE_CURRENT_BINARY_DIR}/Resource.rc)
    target_link_options(${target_name} PRIVATE /SUBSYSTEM:WINDOWS)
    target_link_libraries(${target_name} PRIVATE hello_imgui imgui_node_editor)
    set_target_properties(${target_name} PROPERTIES 
        FOLDER "examples"
    )
endforeach()

#add_subdirectory(blueprints-example)
