cmake_minimum_required(VERSION 3.20)
project(calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator "main.cpp")

# 1. Resolve includes
target_include_directories(calculator PRIVATE "${CMAKE_SOURCE_DIR}/include")

# 2. Link kito (This brings in SDL3 and yaml-cpp automatically via PUBLIC links)
target_link_libraries(calculator PRIVATE kito)

# 3. USE THE MACRO (This is what was missing)
# This will copy your 'views' and 'styles' folders to the output directory
kito_configure_assets(calculator)

# 4. Copy DLLs and Config
add_custom_command(TARGET calculator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        "$<TARGET_FILE_DIR:calculator>"
)

add_custom_command(TARGET calculator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/config.yaml"
        "$<TARGET_FILE_DIR:calculator>"
)