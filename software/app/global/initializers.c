#define DEFAULT_PRIORITY '3'
#define SYSTEM_MEMORY_TOTAL 1048576 // 1048576 bytes = 1024 mega bytes
#define PROCESS_LIMIT 18446744073709551615U
ProcessQueue* FE;
ProcessQueue* FU1;
ProcessQueue* FU2;
ProcessQueue* FU3;
ProcessQueue* FTR;
MemoryPosition* MEMORY;
unsigned long long int process_created;



void init_process_queues() {
    FE = declare_process_queue();
    FU1 = declare_process_queue();
    FU2 = declare_process_queue();
    FU3 = declare_process_queue();
    FTR = declare_process_queue();
}


void init_memory() {
    MEMORY = (MemoryPosition*)malloc(SYSTEM_MEMORY_TOTAL * sizeof(MemoryPosition));
}


void init_process_created() {
    process_created = 0;
}
