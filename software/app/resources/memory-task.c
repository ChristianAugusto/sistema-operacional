typedef struct MemoryTask {
    /*
        1 - allocate_memory
        2 - deallocate_memory
        3 - allocate_memory/deallocate_memory
    */
    unsigned short actionType;
    char* processId;
    unsigned long long int qtdMemory;
    bool autoClean;
    bool* success;
    struct MemoryTask * next;
} MemoryTask;



void clean_memory_task(MemoryTask* mt) {
    if (mt->success != NULL) {
        free(mt->success);
    }
    free(mt);
}


MemoryTask* declare_memory_task(
    unsigned short actionType, char* processId,
    unsigned long long int qtdMemory, bool autoClean
) {
    MemoryTask* mt = (MemoryTask*)malloc(sizeof(MemoryTask));

    mt->actionType = actionType;
    mt->processId = processId;
    mt->qtdMemory = qtdMemory;
    mt->qtdMemory = qtdMemory;
    mt->autoClean = autoClean;
    mt->success = NULL;
    mt->next = NULL;

    return mt;
}


void print_memory_task_default_output(MemoryTask* mt, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tactionType: %u,\n", mt->actionType);
    printf("%s", scape);

    printf("\tprocessId: %s,\n", mt->processId);
    printf("%s", scape);

    printf("\tqtdMemory: %llu,\n", mt->qtdMemory);
    printf("%s", scape);

    printf("\tautoClean: %d,\n", mt->autoClean);
    printf("%s", scape);

    if (mt->success == NULL) {
        printf("\tsuccess: NULL\n");
    }
    else {
        printf("\tsuccess: %d\n", *(mt->success));
    }
    printf("%s", scape);

    printf("}%s\n", division);
}


void print_memory_task_system_tracking_output(MemoryTask* mt, char* scape, char* division) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "{\n");

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tactionType: %u,\n", mt->actionType);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tprocessId: %s,\n", mt->processId);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tqtdMemory: %llu,\n", mt->qtdMemory);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tautoClean: %d,\n", mt->autoClean);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    if (mt->success == NULL) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "\tsuccess: NULL\n");
    }
    else {
        fprintf(SYSTEM_TRACKING_OUTPUT, "\tsuccess: %d\n", *(mt->success));
    }
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "}%s\n", division);
}
