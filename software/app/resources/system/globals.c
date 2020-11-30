char* PROCESS_CREATED;

/*
    0 = Normal
    1 = Turning off
    2 = Finished
    3 = Turned off
    4 = Error

    Use the constants to compare the status
*/
unsigned short SYSTEM_STATUS;

bool DISTRIBUTOR_ON;
bool MEMORY_TASK_WATCHER_ON;
MemoryTaskQueue* MTQ;
MemoryTask* RUNNING_MEMORY_TASK;
