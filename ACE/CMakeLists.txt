cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACERoot)

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

add_subdirectory(ace)
add_subdirectory(ace/SSL)

