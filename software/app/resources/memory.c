typedef struct {
    unsigned long long int processId;
} MemoryPosition;
MemoryPosition* MEMORY;
unsigned long long int MEMORY_USED;



boolean allocate_memory(unsigned long long int processId, unsigned long long int bytes) {
    if (MEMORY_USED == SYSTEM_MEMORY_TOTAL || MEMORY_USED + bytes > SYSTEM_MEMORY_TOTAL) {
        return false;
    }

    unsigned long long int i, allocated_bytes;
    for (
        i = 0, allocated_bytes = 0;
        allocated_bytes < bytes;
        i++
    ) {
        if (MEMORY[i].processId == 0) {
            MEMORY[i].processId = processId;
            allocated_bytes++;
        }
    }

    return true;
}


void deallocate_memory(unsigned long long int processId) {
    unsigned long long int i;
    for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
        if (MEMORY[i].processId == processId) {
            MEMORY[i].processId = 0;
        }
    }
}


void print_memory() {
    FILE* file = fopen("./app/logs/memory.log", "w");

    if (file != NULL) {
        unsigned long long int i;
        for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
            fprintf(file, "%llu\n", MEMORY[i].processId);
        }

        fclose(file);
    }
}


/*
    TODO: Desalocar memória usada pelo processo (recebendo endereços)
*/
