void read_process_from_file() {
    FILE* file = fopen("./app/process.txt", "r");

    if (file == NULL) {
        printf("Error in open ./app/process.txt\n");
        fprintf(SYSTEM_TRACKING_OUTPUT, "Error in open ./app/process.txt\n");
        return;
    }


    ProcessQueue* process_queue_entry = declare_process_queue();

    unsigned int arrivalTime;
    char priority;
    unsigned int processingTime;
    unsigned long long int qtdMemory;
    unsigned short qtdPrinters;
    unsigned short qtdScanners;
    unsigned short qtdModems;
    unsigned short qtdCds;


    while (fscanf(
        file, "%u, %c, %u, %llu, %hu, %hu, %hu, %hu\n",
        &arrivalTime, &priority, &processingTime, &qtdMemory,
        &qtdPrinters, &qtdScanners, &qtdModems, &qtdCds
    ) != EOF) {
        enqueue_process_queue(process_queue_entry, process_creator(
            priority, arrivalTime, processingTime, qtdMemory, qtdPrinters, qtdScanners,
            qtdModems, qtdCds, false
        ));
    }

    fclose(file);

    unsigned int curent_time = 0;
    while (!process_queue_is_empty(process_queue_entry)) {
        printf("curent_time = %u\n", curent_time);
        fprintf(SYSTEM_TRACKING_OUTPUT, "curent_time = %u\n", curent_time);

        int i;
        for (i = 0; i < process_queue_entry->size; i++) {
            Process* aux = peek_process_queue(process_queue_entry);

            if (aux->arrivalTime == curent_time) {
                enqueue_process_queue(
                    FE,
                    dequeue_process_queue(process_queue_entry)
                );
            }
            else {
                break;
            }
        }

        curent_time++;
    }
}
