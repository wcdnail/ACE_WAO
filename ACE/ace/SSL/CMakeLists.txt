cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACE_SSL)

set(VCPKG_APPLOCAL_DEPS OFF)
add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/ACE
)

file(GLOB ACE_SSL_SRCS CONFIGURE_DEPENDS
    "*.h"
    "*.cpp"
)

list(REMOVE_ITEM ACE_SSL_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pch.h"
)

set(ACE_SSL_INCL_LIST ${ACE_SSL_SRCS})

list(REMOVE_ITEM ACE_SSL_SRCS
)

target_sources(${PROJECT_NAME} PRIVATE
    ${ACE_SSL_SRCS}
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ACE_SSL_SRCS})
source_group(".cmake" FILES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pch.h>"
)
source_group(".pch" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.cxx)
foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
    source_group(".pch" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}.dir/${config_type}/cmake_pch.hxx)
endforeach()

target_compile_features(${PROJECT_NAME} PUBLIC
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    _DLL
    ACE_SSL_HAS_DLL=1
    ACE_SSL_BUILD_DLL
)

target_compile_features(${PROJECT_NAME} PUBLIC
    ${ACE_CPP_STD}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Linux>:-fPIC>
)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Windows>:ws2_32.lib>
    $<$<PLATFORM_ID:Windows>:iphlpapi.lib>
    OpenSSL::SSL
    OpenSSL::Crypto
    ACE
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_WHAT_YOU_USE ON
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${ACE_INCL_LIST}
    DESTINATION include/ace/SSL
)
