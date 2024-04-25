cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACE_TAO)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(ACE_CPP_STD cxx_std_23)
    add_compile_options(
        -Wno-unused-value
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(ACE_CPP_STD cxx_std_20)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(ACE_CPP_STD cxx_std_20)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(ACE_CPP_STD cxx_std_23)
    add_compile_options(
        /utf-8
    )
endif()

add_definitions(
    -DACE_HAS_DLL=1
)

add_subdirectory(ACE)
