cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE PATH "VCPKG_ROOT")
if ("${VCPKG_ROOT}" STREQUAL "")
    message(WARNING ">>>> VCPKG_ROOT is empty!")
endif()

if (NOT VCPKG_TARGET_TRIPLET OR "${VCPKG_TARGET_TRIPLET}" STREQUAL "x64-")
    if (WIN32)
        set(VCPKG_TARGET_TRIPLET x64-windows)
    elseif (MSYS OR MINGW)
        set(VCPKG_TARGET_TRIPLET x64-mingw-dynamic)
    else()
        set(VCPKG_TARGET_TRIPLET x64-linux)
    endif()
    message(STATUS ">>>> VCPKG triplet setup from cmake: ${VCPKG_TARGET_TRIPLET}")
endif()

set(VCPKG_INSTALLED_DIR "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(VCPKG_INSTALLED_CONF_DIR "${VCPKG_INSTALLED_DIR}/debug")
else()
    set(VCPKG_INSTALLED_CONF_DIR "${VCPKG_INSTALLED_DIR}")
endif()

project(ACE_TAO)

option(ACE_BUILD_ASE_SSL    "Build ACE SSL module" ON)
option(ACE_BUILD_ASE_ASNMP  "Build ACE ASNMO module" OFF)
option(ACE_BUILD_EXAMPLES   "Build ACE examples" ON)

if (NOT OPENSSL_ROOT_DIR)
    set(OPENSSL_ROOT_DIR ${VCPKG_INSTALLED_DIR})
    message(STATUS ">>>> OPENSSL_ROOT_DIR setup from cmake: ${VCPKG_INSTALLED_DIR}")
endif()

find_package(OpenSSL REQUIRED)

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
    add_definitions(
        -D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
    )
endif()

add_definitions(
    -DACE_HAS_DLL=1
)

set(BUILD_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${VCPKG_TARGET_TRIPLET})

add_subdirectory(ACE)
