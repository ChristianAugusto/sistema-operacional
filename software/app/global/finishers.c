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