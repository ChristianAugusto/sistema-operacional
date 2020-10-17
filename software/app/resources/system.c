ProcessQueue* FE;
ProcessQueue* UQ;
ProcessQueue* UQ2;
ProcessQueue* UQ3;
ProcessQueue* RTQ;
unsigned long long int process_created;



void init_cpus() {
    CPUS = (CPU*)malloc(CPUS_TOTAL * sizeof(CPU));
}


void init_memory() {
    MEMORY = (MemoryPosition*)malloc(SYSTEM_MEMORY_TOTAL * sizeof(MemoryPosition));
    MEMORY_USED = 0;
}


void init_cd_drivers() {
    CD_DRIVERS = (CD_DRIVER*)malloc(CD_DRIVERS_TOTAL * sizeof(CD_DRIVER));
}


void init_modems() {
    MODEMS = (MODEM*)malloc(MODEMS_TOTAL * sizeof(MODEM));
}


void init_printers() {
    PRINTERS = (PRINTER*)malloc(PRINTERS_TOTAL * sizeof(PRINTER));
}


void init_scanners() {
    SCANNERS = (SCANNER*)malloc(SCANNERS_TOTAL * sizeof(SCANNER));
}


void init_process_queues() {
    FE = declare_process_queue();
    UQ = declare_process_queue();
    UQ2 = declare_process_queue();
    UQ3 = declare_process_queue();
    RTQ = declare_process_queue();
}


void init_process_created() {
    process_created = 0;
}


void finish_cpus() {
    free(CPUS);
}


void finish_memory() {
    free(MEMORY);
}


void finish_cd_drivers() {
    free(CD_DRIVERS);
}


void finish_modems() {
    free(MODEMS);
}


void finish_printers() {
    free(PRINTERS);
}


void finish_scanners() {
    free(SCANNERS);
}


void finish_process_queues() {
    clean_process_queue(FE);
    clean_process_queue(UQ);
    clean_process_queue(UQ2);
    clean_process_queue(UQ3);
    clean_process_queue(RTQ);
}


void initializers() {
    init_cpus();
    init_memory();
    init_cd_drivers();
    init_modems();
    init_printers();
    init_scanners();
    init_process_queues();
    init_process_created();
}


void finishers() {
    finish_cpus();
    finish_memory();
    finish_cd_drivers();
    finish_modems();
    finish_printers();
    finish_scanners();
    finish_process_queues();
}


/**
 *  System process creator
 */
Process* process_creator(char pr, boolean enqueue) {
    if (process_created > SYSTEM_PROCESS_LIMIT) {
        /*
            TODO: Finish program in this condition
        */
        return NULL;
    }

    Process* new_process = declare_process(process_created+1, pr);

    if (enqueue) {
        enqueue_process_queue(FE, new_process);

        return NULL;
    }
    else {
        return new_process;
    }
}
