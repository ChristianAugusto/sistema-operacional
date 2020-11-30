typedef struct Process {
    char* id;
    char priority;
    unsigned int arrivalTime;
    unsigned int processingTime; // Seconds
    unsigned long long int qtdMemory;
    unsigned short qtdPrinters;
    unsigned short qtdScanners;
    unsigned short qtdModems;
    unsigned short qtdCds;
    unsigned int processedTime;
    unsigned int curentProcessQueueId;
    struct Process * next;
} Process;



void clean_process(Process* p) {
    free(p->id);
    free(p);
}


/**
 *  Process declare. Do not call this function directly.
 *  To create process, use process_creator.
 */
Process* declare_process(
    char* id, char priority, unsigned int arrivalTime, unsigned int processingTime,
    unsigned long long int qtdMemory, unsigned short qtdPrinters,
    unsigned short qtdScanners, unsigned short qtdModems, unsigned short qtdCds
) {
    Process* p = (Process*)malloc(sizeof(Process));

    p->id = id;
    p->priority = priority;
    p->arrivalTime = arrivalTime;
    p->processingTime = processingTime;
    p->qtdMemory = qtdMemory;
    p->qtdPrinters = qtdPrinters;
    p->qtdScanners = qtdScanners;
    p->qtdModems = qtdModems;
    p->qtdCds = qtdCds;
    p->processedTime = 0;
    p->next = NULL;

    return p;
}


void print_process_default_output(Process* p, char* scape, char* division) {
    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tid: %s,\n", p->id);
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
