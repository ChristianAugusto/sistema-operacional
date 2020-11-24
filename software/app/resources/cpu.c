typedef struct {
    Process* running_process;
    bool inUse;
    bool dispatcherOn;
    pthread_t dispatcher_thread_id;
} CPU;
CPU* CPUS;
