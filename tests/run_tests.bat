@echo off
@echo This is the NT version of the one-button ACE tests.
@echo on
@echo Starting tests...

Barrier_Test
Buffer_Stream_Test
CPP_Test
Future_Test
Handle_Set_Test
Mem_Map_Test
Mutex_Test
Naming_Test
Priority_Buffer_Test
Reactors_Test
Reactor_Timer_Test
Reader_Writer_Test
Recursive_Mutex_Test
Shared_Memory_MM_Test
SPIPE_Test
SString_Test
Task_Test
Thread_Manager_Test
Thread_Pool_Test
Timer_Queue_Test
Time_Service_Test
Time_Value_Test
Tokens_Test
TSS_Test
UPIPE_SAP_Test

@echo Tests complete...
