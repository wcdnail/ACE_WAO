cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(C++NPv2)

set(VCPKG_APPLOCAL_DEPS OFF)
set(ACE_CURRENT_EXAMPLE_ROOT "${PROJECT_NAME}")

ACE_add_example_ex(CLD
    SOURCES
        Client_Logging_Daemon.cpp
        Logging_Acceptor.cpp
        Logging_Event_Handler.cpp
        Logging_Handler.cpp
    DLL ON
    DEFS
        CLD_BUILD_DLL
)
ACE_add_example_ex(AC_CLD
    SOURCES
        AC_Client_Logging_Daemon.cpp
        Logging_Handler.cpp
        C++NPv2.mpc
    DLL ON
    DEFS
        AC_CLD_BUILD_DLL
)
ACE_add_example_ex(AIO_CLD
    SOURCES
        AIO_Client_Logging_Daemon.cpp
    DLL ON
    DEFS
        AIO_CLD_BUILD_DLL
)
ACE_add_example_ex(SLD
    SOURCES
        SLD.cpp
        Logging_Acceptor.cpp
        Logging_Event_Handler.cpp
        Logging_Handler.cpp
    DLL ON
    DEFS
        SLD_BUILD_DLL
)
ACE_add_example_ex(SLDex
    SOURCES
        Logging_Acceptor.cpp
        Logging_Event_Handler.cpp
        Logging_Event_Handler_Ex.cpp
        Logging_Handler.cpp
        Reactor_Logging_Server_Adapter.cpp
        Server_Shutdown.cpp
        SLDex.cpp
    DLL ON
    DEFS
        LDEX_BUILD_DLL
)
ACE_add_example_ex(TPCLS
    SOURCES
        TPC_Logging_Server.cpp
        Logging_Handler.cpp
    DLL ON
    DEFS
        TPCLS_BUILD_DLL
    LIBS
        ACE_SSL
)
ACE_add_example_ex(TPLS SOURCES
    SOURCES
        Logging_Acceptor.cpp
        Logging_Event_Handler.cpp
        Logging_Handler.cpp
        TP_Logging_Server.cpp
    DLL ON
    DEFS
        TPLS_BUILD_DLL
)

ACE_add_example_ex(Configurable_Log_Server SOURCES
    Configurable_Logging_Server.cpp
    Service_Reporter.cpp
)
ACE_add_example_ex(Display_Logfile SOURCES
    display_logfile.cpp
)
ACE_add_example_ex(Reactor_Log_Server SOURCES
    Logging_Acceptor.cpp
    Logging_Event_Handler.cpp
    Logging_Event_Handler_Ex.cpp
    Logging_Handler.cpp
    Reactor_Logging_Server.cpp
)
ACE_add_example_ex(Select_Reactor_Log_Server SOURCES
    Logging_Acceptor.cpp
    Logging_Event_Handler.cpp
    Logging_Event_Handler_Ex.cpp
    Logging_Handler.cpp
    Select_Reactor_Logging_Server.cpp
)
ACE_add_example_ex(SR_Configurable_Log_Server SOURCES
    SR_Configurable_Logging_Server.cpp
)
ACE_add_example_ex(TP_Reactor_Log_Server SOURCES
    Logging_Acceptor.cpp
    Logging_Event_Handler.cpp
    Logging_Event_Handler_Ex.cpp
    Logging_Handler.cpp
    TP_Reactor_Logging_Server.cpp
)
ACE_add_example_ex(WFMO_Reactor_Log_Server SOURCES
    Logging_Acceptor.cpp
    Logging_Event_Handler.cpp
    Logging_Event_Handler_Ex.cpp
    Logging_Handler.cpp
    WFMO_Reactor_Logging_Server.cpp
)
