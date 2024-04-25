cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(SSL_SAP)

set(VCPKG_APPLOCAL_DEPS OFF)
set(ACE_CURRENT_EXAMPLE_ROOT "IPC_SAP/${PROJECT_NAME}")

ACE_add_example_ex(${PROJECT_NAME}-client
    SOURCES
        SSL-client.cpp
    LIBS
        ACE_SSL
)
ACE_add_example_ex(${PROJECT_NAME}-client_simple
    SOURCES
        SSL-client-simple.cpp
    LIBS
        ACE_SSL
)
ACE_add_example_ex(${PROJECT_NAME}-server
    SOURCES
        SSL-server.cpp
    LIBS
        ACE_SSL
)
ACE_add_example_ex(${PROJECT_NAME}-server_fancy
    SOURCES
        SSL-server-fancy.cpp
    LIBS
        ACE_SSL
)
ACE_add_example_ex(${PROJECT_NAME}-server_poll
    SOURCES
        SSL-server-poll.cpp
    LIBS
        ACE_SSL
)
ACE_add_example_ex(${PROJECT_NAME}-server_simple
    SOURCES
        SSL-server-simple.cpp
    LIBS
        ACE_SSL
)
