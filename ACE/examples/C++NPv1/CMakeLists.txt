cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(C++NPv1)

set(VCPKG_APPLOCAL_DEPS OFF)
set(ACE_CURRENT_EXAMPLE_ROOT "${PROJECT_NAME}")

ACE_add_example_ex(Iterative_Logging_Server
    SOURCES
        Iterative_Logging_Server.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(Logging_Client
    SOURCES
        Logging_Client.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(PPC_Logging_Server
    SOURCES
        Process_Per_Connection_Logging_Server.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(Reactive_Logging_Server
    SOURCES
        Reactive_Logging_Server.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(Reactive_Logging_Server_Ex
    SOURCES
        Reactive_Logging_Server_Ex.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(RTTPC_Logging_Server
    SOURCES
        RT_Thread_Per_Connection_Logging_Server.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)

ACE_add_example_ex(TPC_Logging_Server
    SOURCES
        Thread_Per_Connection_Logging_Server.cpp
        Logging_Server.cpp
        Logging_Handler.cpp
    CMD_LINE "27073"
)
