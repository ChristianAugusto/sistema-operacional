typedef struct {
    char* processId;
} MemoryPosition;
MemoryPosition* MEMORY;
unsigned long long int MEMORY_USED;



bool system_memory_is_full() {
    return MEMORY_USED == SYSTEM_MEMORY_TOTAL;
}


bool system_memory_will_have_space(unsigned long long int bytes) {
    return MEMORY_USED + bytes <= SYSTEM_MEMORY_TOTAL;
}


bool allocate_memory(char* processId, unsigned long long int bytes) {
    bytes *= SYSTEM_MEMORY_SCALE;

    if (system_memory_is_full() || !system_memory_will_have_space(bytes)) {
        return false;
    }

    unsigned long long int i, j, k;
    for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
        if (MEMORY[i].processId == NULL) {
            unsigned long long int available_bytes = 1U;

            for (j = i+1; available_bytes < bytes && j < SYSTEM_MEMORY_TOTAL; j++) {
                if (MEMORY[j].processId == NULL) {
                    available_bytes++;
                }
                else {
                    i = j;
                    continue;
                }
            }

            if (available_bytes == bytes) {
                for (j = i, k = 0; k < bytes; j++, k++) {
                    MEMORY[j].processId = str_copy(processId);
                }

                MEMORY_USED += bytes;

                return true;
            }
        }
    }

    return false;
}


void deallocate_memory(char* processId) {
    unsigned long long int i;
    for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
        if (str_equals(MEMORY[i].processId, processId)) {
            free(MEMORY[i].processId);
            MEMORY[i].processId = NULL;
            MEMORY_USED -= 1 * SYSTEM_MEMORY_SCALE;
        }
    }
}


void print_memory() {
    FILE* file = fopen("./app/logs/memory.log", "w");

    if (file != NULL) {
        unsigned long long int i;
        for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
            if (MEMORY[i].processId == NULL) {
                fprintf(file, "\n");
            }
            else {
                fprintf(file, "%s\n", MEMORY[i].processId);
            }
        }

        fclose(file);
    }
}
