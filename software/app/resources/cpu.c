typedef struct {
    unsigned long long int processId;
    boolean inUse;
    pthread_t dispatcher_thread_id;
} CPU;
CPU* CPUS;
