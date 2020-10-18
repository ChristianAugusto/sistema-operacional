/**
 *  System process creator
 */
Process* process_creator(char pr, boolean enqueue) {
    if (PROCESS_CREATED > SYSTEM_PROCESS_LIMIT) {
        /*
            TODO: Finish program in this condition
        */
        return NULL;
    }

    Process* new_process = declare_process(PROCESS_CREATED+1, pr);

    if (enqueue) {
        enqueue_process_queue(FE, new_process);

        return NULL;
    }
    else {
        return new_process;
    }
}
