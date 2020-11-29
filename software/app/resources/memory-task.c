typedef struct MemoryTask {
    /*
        1 - allocate_memory
        2 - deallocate_memory
        3 - allocate_memory/deallocate_memory
    */
    unsigned short actionType;
    char* processId;
    unsigned long long int qtdMemory;
    bool* success;
    struct MemoryTask * next;
} MemoryTask;



void clean_memory_task(MemoryTask* mt) {
    free(mt->success);
    free(mt);
}


MemoryTask* declare_memory_task(
    unsigned short actionType, char* processId,
    unsigned long long int qtdMemory
) {
    MemoryTask* mt = (MemoryTask*)malloc(sizeof(MemoryTask));

    mt->actionType = actionType;
    mt->processId = processId;
    mt->qtdMemory = qtdMemory;
    mt->qtdMemory = qtdMemory;
    mt->success = NULL;
    mt->next = NULL;

    return mt;
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
