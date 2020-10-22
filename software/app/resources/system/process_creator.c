/**
 *  System process creator
 */
Process* process_creator(char pr, boolean enqueue) {
    PROCESS_CREATED = str_incrementIds(PROCESS_CREATED);

    Process* new_process = declare_process(str_copy(PROCESS_CREATED), pr);

    if (enqueue) {
        enqueue_process_queue(FE, new_process);

        return NULL;
    }
    else {
        return new_process;
    }
}
