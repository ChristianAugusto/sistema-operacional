typedef struct {
    char* processId;
} MemoryPosition;
MemoryPosition* MEMORY;
unsigned long long int MEMORY_USED;

typedef struct MemoryTask {
    /*
        1 - allocate_memory
        2 - deallocate_memory
        3 - deallocate_memory - allocate_memory
    */
    unsigned short actionType;
    struct MemoryTask * next;
} MemoryTask;




bool system_memory_is_full() {
    return MEMORY_USED == SYSTEM_MEMORY_TOTAL;
}


bool system_memory_will_have_space(unsigned long long int bytes) {
    return MEMORY_USED + bytes <= SYSTEM_MEMORY_TOTAL;
}


/**
 *  System memory allocation. Do not call this function directly.
 */
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
                    break;
                }
            }

            if (available_bytes == bytes) {
                for (j = i, k = 0; k < bytes; j++, k++) {
                    MEMORY[j].processId = str_copy(processId);
                }

                MEMORY_USED += bytes;

                return true;
            }

            i = j;
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


void print_memory_task_default_output(MemoryTask* mt, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\actionType: %u\n", mt->actionType);

    printf("%s", scape);

    printf("}%s\n", division);
}


void print_memory_task_system_tracking_output(MemoryTask* mt, char* scape, char* division) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "{\n");

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\actionType: %u\n", mt->actionType);

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "}%s\n", division);
}
