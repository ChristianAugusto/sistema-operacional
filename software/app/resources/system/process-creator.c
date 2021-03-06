/**
 *  System process creator
 */
Process* process_creator(
    char priority, unsigned int arrivalTime, unsigned int processingTime,
    unsigned long long int qtdMemory, unsigned short qtdPrinters,
    unsigned short qtdScanners, unsigned short qtdModems, unsigned short qtdCds,
    bool enqueue
) {
    PROCESS_CREATED = str_incrementIds(PROCESS_CREATED);

    Process* new_process = declare_process(
        str_copy(PROCESS_CREATED), priority, arrivalTime, processingTime, qtdMemory,
        qtdPrinters, qtdScanners, qtdModems, qtdCds
    );

    fprintf(SYSTEM_TRACKING_OUTPUT, "Creating new process...");
    print_process_system_tracking_output(new_process, "\t", "");

    if (enqueue) {
        enqueue_process_queue(FE, new_process);

        return NULL;
    }
    else {
        return new_process;
    }
}
