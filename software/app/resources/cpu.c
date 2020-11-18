typedef struct {
    unsigned long long int processId;
    bool inUse;
    bool dispatcherOn;
    pthread_t dispatcher_thread_id;
} CPU;
CPU* CPUS;
