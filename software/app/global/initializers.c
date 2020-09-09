#define SYSTEM_MEMORY_BASE 73728 // 73728 bytes = 72 kbytes
#define SYSTEM_MEMORY_TOTAL 1048576 // 1048576 bytes = 1024 mega bytes
ProcessQueue* FE;
ProcessQueue* FU1;
ProcessQueue* FU2;
ProcessQueue* FU3;
ProcessQueue* FTR;
unsigned long long int memory_allocated; // bytes



void init_process_queues() {
    FE = declare_process_queue();
    FU1 = declare_process_queue();
    FU2 = declare_process_queue();
    FU3 = declare_process_queue();
    FTR = declare_process_queue();
}


void init_memory_usage() {
    memory_allocated = SYSTEM_MEMORY_BASE;
}


void read_process_from_file() {
    /*
        TODO: Criar função para iniciar processos
        lidos de um arquivo de entrada
    */
}