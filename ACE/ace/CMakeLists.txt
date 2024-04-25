cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

project(ACE)

set(VCPKG_APPLOCAL_DEPS OFF)
add_library(${PROJECT_NAME} SHARED)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/ACE
)

file(GLOB ACE_SOURCES CONFIGURE_DEPENDS
    "*.h"
    "*.cpp"
)

list(REMOVE_ITEM ACE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pch.h"
)

set(ACE_INCL_LIST ${ACE_SOURCES})

list(REMOVE_ITEM ACE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/ARGV.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Arg_Shifter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Array_Base.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Array_Map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asynch_Acceptor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asynch_Connector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Atomic_Op_GCC_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Atomic_Op_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Auto_Event.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Auto_Functor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Auto_IncDec_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Auto_Ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Based_Pointer_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bound_Ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cached_Connect_Strategy_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cache_Map_Manager_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Caching_Strategies_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Caching_Utility_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cleanup_Strategies_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Condition_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Connector.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Containers_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Countdown_Time_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dump_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env_Value_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Event_Handler_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Framework_Component_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Free_List.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Functor_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Future.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Future_Set.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Guard_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hash_Cache_Map_Manager_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hash_Map_Manager_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hash_Map_With_Allocator_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hash_Multi_Map_Manager_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Intrusive_Auto_Ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Intrusive_List.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Intrusive_List_Node.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/IOStream_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Local_Name_Space_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Lock_Adapter_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/LOCK_SOCK_Acceptor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Malloc_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Managed_Object.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Manual_Event.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map_Manager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Message_Block_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Message_Queue_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Metrics_Cache_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Module.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Obstack_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pair_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RB_Tree.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Reactor_Token_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Refcountable_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Refcounted_Auto_Ptr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Reverse_Lock_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Select_Reactor_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Singleton.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Strategies_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Stream.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Stream_Modules.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/String_Base.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Svc_Handler.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Task_Ex_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Task_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Test_and_Set.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timeprobe_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_Hash_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_Heap_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_List_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_Queue_Iterator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_Queue_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Timer_Wheel_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Time_Policy_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Time_Value_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Tokenizer_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TSS_T.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Typed_SV_Message.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Typed_SV_Message_Queue.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Unbounded_Queue.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Unbounded_Set.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Unbounded_Set_Ex.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Vector_T.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE
    ${ACE_SOURCES}
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ACE_SOURCES})
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
    ACE_BUILD_DLL
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
    DESTINATION include/ace
)
