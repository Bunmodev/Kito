# Kito Framework Configuration File
include(CMakeParseArguments)

# --- 1. The Build Automator ---
function(kito_build_project TARGET_NAME)
    set(options EXECUTABLE STATIC SHARED)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(KITO "${options}" "" "${multiValueArgs}" ${ARGN})

    # This ensures the output is local to the example/project
    set(LOCAL_OUT "${CMAKE_CURRENT_BINARY_DIR}/output")

    if(KITO_EXECUTABLE)
        add_executable(${TARGET_NAME} ${KITO_SOURCES})
        set_target_properties(${TARGET_NAME} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY "${LOCAL_OUT}"
        )
    endif()

    # Link the Engine
    target_link_libraries(${TARGET_NAME} PRIVATE kito)
endfunction()

function(kito_register_vms VM_DIR MAIN_TARGET)
    file(GLOB VM_SOURCES "${VM_DIR}/*.cpp")
    set(LOCAL_OUT "${CMAKE_CURRENT_BINARY_DIR}/output")

    foreach(VM_SOURCE ${VM_SOURCES})
        get_filename_component(VM_NAME ${VM_SOURCE} NAME_WE)
        add_library(${VM_NAME} SHARED ${VM_SOURCE})
        
        target_link_libraries(${VM_NAME} PRIVATE kito)
        
        set_target_properties(${VM_NAME} PROPERTIES 
            # Force DLL into /bin
            RUNTIME_OUTPUT_DIRECTORY "${LOCAL_OUT}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${LOCAL_OUT}/bin"
            # Keep the .dll.a "junk" out of the clean folders
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/artifacts"
            PREFIX "" 
        )
        add_dependencies(${MAIN_TARGET} ${VM_NAME})
    endforeach()
endfunction()

macro(kito_configure_assets TARGET_NAME)
    set(LOCAL_OUT "${CMAKE_CURRENT_BINARY_DIR}/output")
    set(KITO_RES_DIR "${LOCAL_OUT}/.kito")

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        # 1. Create the structure
        COMMAND ${CMAKE_COMMAND} -E make_directory "${LOCAL_OUT}/assets"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${LOCAL_OUT}/bin"
        
        # 2. Copy the Bootloader (config.yaml) to Root
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/config.yaml" "${LOCAL_OUT}/config.yaml"
        
        # 3. Organize Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/src/views" "${LOCAL_OUT}/assets/views"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/src/models" "${LOCAL_OUT}/assets/models"
        
        # 4. Move Driver DLLs to /bin
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:SDL3::SDL3>" "${LOCAL_OUT}/bin/"
        
        COMMENT "Kito SDK: Finalizing premeditated folder structure..."
    )
endmacro() 