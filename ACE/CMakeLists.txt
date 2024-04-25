cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACERoot)

set(CURRENT_SOLUTION_FOLDER "ACE")

if (WIN32 OR MINGW OR MSYS)
    set(config_h_contents "#include \"ace/config-windows.h\"\n")
elseif (UNIX)
    set(config_h_contents "#include \"ace/config-linux.h\"\n")
elseif (OSX)
    set(config_h_contents "#include \"ace/config-macosx.h\"\n")
endif()

#string(APPEND config_h_contents "#define ACE_USES_WCHAR\n") # no no no....
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    string(APPEND config_h_contents "#define ACE_HAS_DUMP 1\n")
Endif()

file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/ace/config.h" "${config_h_contents}")

set(ACE_ROOT_FILES
    ACE.mwc
    ACE-INSTALL.html
    AUTHORS
    CMakeLists.txt
    COPYING
    NEWS
    PROBLEM-REPORT-FORM
    README
    THANKS
    VERSION.txt
)
add_custom_target(${PROJECT_NAME} SOURCES ${ACE_ROOT_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${CURRENT_SOLUTION_FOLDER}")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ACE_ROOT_FILES})

add_subdirectory(ace)
if (ACE_BUILD_ASE_SSL)
    add_subdirectory(ace/SSL)
endif()
if (ACE_BUILD_ASE_ASNMP)
    add_subdirectory(ASNMP/asnmp)
endif()
if (ACE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
