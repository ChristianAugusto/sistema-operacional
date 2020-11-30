typedef struct PeripheralsTask {
    unsigned short qtdPrinters;
    unsigned short qtdScanners;
    unsigned short qtdModems;
    unsigned short qtdCds;
    bool autoClean;
    bool* success;
    struct PeripheralsTask * next;
} PeripheralsTask;



void clean_peripherals_task(PeripheralsTask* mt) {
    free(mt);
}


PeripheralsTask* declare_peripherals_task(
    
) {
    PeripheralsTask* mt = (PeripheralsTask*)malloc(sizeof(PeripheralsTask));

    
    mt->next = NULL;

    return mt;
}


void print_peripherals_task_default_output(PeripheralsTask* mt, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tautoClean: %d,\n", mt->autoClean);
    printf("%s", scape);

    printf("}%s\n", division);
}


void print_peripherals_task_system_tracking_output(PeripheralsTask* mt, char* scape, char* division) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "{\n");

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tautoClean: %d\n", mt->autoClean);
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "}%s\n", division);
}
