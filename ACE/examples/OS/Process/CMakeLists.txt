cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(Process)

set(VCPKG_APPLOCAL_DEPS OFF)
set(ACE_CURRENT_EXAMPLE_ROOT "OS/${PROJECT_NAME}")

ACE_add_example_ex(${PROJECT_NAME}-imore
    SOURCES
        imore.cpp
)
ACE_add_example_ex(${PROJECT_NAME}-process
    SOURCES
        process.cpp
)
