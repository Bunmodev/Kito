cmake_minimum_required(VERSION 3.20)
project(Kito)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/SDL)
add_subdirectory(external/yaml-cpp)

set(ENGINE_SRC 
    "src/core/input.cpp"
    "src/core/window.cpp"
    "src/core/application.cpp"
    "src/ui/core/ui.cpp" 
    "src/ui/core/inflate.cpp"
    "src/ui/widgets/widget.cpp"
    "src/ui/widgets/button.cpp"
    "src/ui/widgets/panel.cpp"
    "src/ui/widgets/container.cpp"
    "src/ui/layout/msanifu.cpp" 
    "src/graphics/renderer/renderer.cpp" 
    "src/utils/configParser.cpp"
    "src/utils/tokenizer.cpp"
    "src/utils/Lexer.cpp" 
    "src/utils/kitoParser.cpp" 
    "src/utils/kitoInterpreter.cpp"
    "src/services/configManager.cpp"
    "src/services/viewManager.cpp" 
    "src/services/vfs.cpp"
    "src/mvvm/model.cpp"
    "src/mvvm/view.cpp" 
    "src/mvvm/viewModel.cpp"
)

add_library(kito STATIC ${ENGINE_SRC})

target_link_libraries(kito
   PUBLIC SDL3::SDL3  
   PUBLIC yaml-cpp
)

target_include_directories(kito PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/external/miniaudio
)

macro(kito_configure_assets TARGET_NAME)
    # Use CURRENT_SOURCE_DIR so it finds the views for the specific example
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/views"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/src/views"
        COMMENT "Deploying Kito Views for ${TARGET_NAME}..."
    )

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/models"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/src/models"
        COMMENT "Deploying Kito Models for ${TARGET_NAME}..."
    )

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/styles"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/styles"
        COMMENT "Deploying Kito Styles for ${TARGET_NAME}..."
    )
endmacro() 

add_subdirectory(examples) 
