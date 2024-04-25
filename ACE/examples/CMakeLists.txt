cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACExamples)

set(CURRENT_SOLUTION_FOLDER "ACE/examples")

#message(STATUS "Build example : ${EXA_NAME} ${EXA_CMD_LINE}")
#foreach (EAX_S IN LISTS EXA_SOURCES)
#    message("    >> ${EAX_S}")
#endforeach()

function(ACE_add_example_ex EXA_NAME)
    cmake_parse_arguments(
        EXA
        "DLL;LIB"
        "CMD_LINE"
        "SOURCES;DEFS;CFLAGS;LIBS"
        ${ARGN}
    )
    #message(STATUS ">>>> Build example : ${EXA_NAME} DLL=${EXA_DLL} DEFS=${EXA_DEFS}")
    if (EXA_DLL)
        add_library(${EXA_NAME} SHARED)
    elseif (EXA_LIB)
        add_library(${EXA_NAME} STATIC)
    else()
        add_executable(${EXA_NAME})
    endif()
    target_include_directories(${EXA_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/ACE
    )
    target_include_directories(${EXA_NAME} SYSTEM PRIVATE
        ${VCPKG_INSTALLED_DIR}/include
    )
    target_sources(${EXA_NAME} PRIVATE
        ${EXA_SOURCES}
     )
    set_target_properties(${EXA_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}/${ACE_CURRENT_EXAMPLE_ROOT}")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EXA_SOURCES})
    target_compile_features(${EXA_NAME} PUBLIC
        ${ACE_CPP_STD}
    )
    target_compile_definitions(${EXA_NAME} PUBLIC
        ${EXA_DEFS}
    )
    target_compile_options(${EXA_NAME} PUBLIC
        $<$<PLATFORM_ID:Linux>:-fPIC>
        ${EXA_CFLAGS}
    )
    target_link_libraries(${EXA_NAME} PUBLIC
        ACE
        ${EXA_LIBS}
    )
    set_target_properties(${EXA_NAME} PROPERTIES
            LINK_WHAT_YOU_USE ON
            ARCHIVE_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUTPUT_DIR}"
    )
    if (MSVC)
        set(DBG_PATH "PATH=$(PATH);${VCPKG_INSTALLED_CONF_DIR}\\bin")
        set_target_properties(${EXA_NAME} PROPERTIES
            VS_DEBUGGER_ENVIRONMENT "${DBG_PATH}"
            VS_DEBUGGER_COMMAND_ARGUMENTS "${EXA_CMD_LINE}"
        )
    endif()
endfunction()


set(EXA_ROOT_FILES
    README
    CMakeLists.txt
    example_base.mpb
    examples.mwc
)
add_custom_target(${PROJECT_NAME} SOURCES ${EXA_ROOT_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EXA_ROOT_FILES})

add_subdirectory(APG)
add_subdirectory(ASX)
add_subdirectory(Bounded_Packet_Relay)
add_subdirectory(C++NPv1)
add_subdirectory(C++NPv2)
add_subdirectory(ConfigViewer)
add_subdirectory(Connection)
add_subdirectory(DLL)
add_subdirectory(Export)
add_subdirectory(IOStream)
add_subdirectory(IPC_SAP)
add_subdirectory(Logger)
add_subdirectory(Log_Msg)
add_subdirectory(Map_Manager)
add_subdirectory(Mem_Map)
add_subdirectory(Misc)
add_subdirectory(Monitor)
add_subdirectory(Naming)
add_subdirectory(NT_Service)
add_subdirectory(OS)
add_subdirectory(QOS)
add_subdirectory(Reactor)
add_subdirectory(Registry)
add_subdirectory(Semaphores)
add_subdirectory(Service_Configurator)
add_subdirectory(Shared_Malloc)
add_subdirectory(Shared_Memory)
add_subdirectory(Smart_Pointers)
add_subdirectory(Synch)
add_subdirectory(System_V_IPC)
add_subdirectory(Threads)
add_subdirectory(Timer_Queue)
add_subdirectory(Web_Crawler)
