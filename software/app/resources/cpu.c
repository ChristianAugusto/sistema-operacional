typedef struct {
    unsigned long long int processId;
    bool inUse;
    pthread_t dispatcher_thread_id;
} CPU;
CPU* CPUS;
