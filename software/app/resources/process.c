typedef struct process {
    char* id;
    char* tempoDeChegada;
    char priority;
    unsigned int processorTime;
    unsigned long long int memory;
    unsigned short qtdPrinters;
    unsigned short qtdScanners;
    unsigned short qtdScanners;
    unsigned short qtdModems;
    unsigned short qtdCds;
    struct process * next;
} Process;



/**
 *  Process declare. Do not call this function directly.
 *  To create process, use process_creator.
 */
Process* declare_process(char* id, char pr) {
    Process* p = (Process*)malloc(sizeof(Process));

    p->id = id;
    p->priority = pr;

    return p;
}


void print_process_default_output(Process* p, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tid: %s\n", p->id);

    printf("%s", scape);

    printf("\tpriority: %c\n", p->priority);

    printf("%s", scape);

    printf("}%s\n", division);
}


void print_process_system_tracking_output(Process* p, char* scape, char* division) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "{\n");

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tid: %s\n", p->id);

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "\tpriority: %c\n", p->priority);

    fprintf(SYSTEM_TRACKING_OUTPUT, "%s", scape);

    fprintf(SYSTEM_TRACKING_OUTPUT, "}%s\n", division);
}
