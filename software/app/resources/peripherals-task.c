typedef struct PeripheralsTask {
    /*
        1 - allocate_peripheral
        2 - deallocate_peripheral
    */
    unsigned short actionType;
    char* processId;
    unsigned short qtdPrinters;
    unsigned short qtdScanners;
    unsigned short qtdModems;
    unsigned short qtdCds;
    bool autoClean;
    bool* success;
    struct PeripheralsTask * next;
} PeripheralsTask;



void clean_peripherals_task(PeripheralsTask* pt) {
    free(pt->processId);
    if (pt->success != NULL) {
        free(pt->success);
    }
    free(pt);
}


PeripheralsTask* declare_peripherals_task(
    unsigned short actionType, char* processId, unsigned short qtdPrinters, unsigned short qtdScanners,
    unsigned short qtdModems, unsigned short qtdCds, bool autoClean
) {
    PeripheralsTask* pt = (PeripheralsTask*)malloc(sizeof(PeripheralsTask));

    pt->actionType = actionType;
    pt->processId = processId;
    pt->qtdPrinters = qtdPrinters;
    pt->qtdScanners = qtdScanners;
    pt->qtdModems = qtdModems;
    pt->qtdCds = qtdCds;
    pt->autoClean = autoClean;
    pt->success = NULL;
    pt->next = NULL;

    return pt;
}


void print_peripherals_task_default_output(PeripheralsTask* pt, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tautoClean: %d,\n", pt->autoClean);
    printf("%s", scape);

    printf("}%s\n", division);
}


void print_peripherals_task_system_tracking_output(PeripheralsTask* pt, char* scape, char* division) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "{\n");

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tautoClean: %d\n", pt->autoClean);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "}%s\n", division);
}
