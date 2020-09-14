
ProcessQueue* FE;
ProcessQueue* FU1;
ProcessQueue* FU2;
ProcessQueue* FU3;
ProcessQueue* FTR;
unsigned long long int process_created;



void init_process_queues() {
    FE = declare_process_queue();
    FU1 = declare_process_queue();
    FU2 = declare_process_queue();
    FU3 = declare_process_queue();
    FTR = declare_process_queue();
}


void init_memory() {
    MEMORY = (MemoryPosition*)malloc(SYSTEM_MEMORY_TOTAL * sizeof(MemoryPosition));
    MEMORY_USED = 0;
}


void init_process_created() {
    process_created = 0;
}


void finish_process_queues() {
    clean_process_queue(FE);
    clean_process_queue(FU1);
    clean_process_queue(FU2);
    clean_process_queue(FU3);
    clean_process_queue(FTR);
}


void finish_memory() {
    free(MEMORY);
}

/**
 *  Criador de processos do sistema.
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
