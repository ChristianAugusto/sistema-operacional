/**
 *  System distributor watcher: Verify if has process in FE.
 */
void* distributor_watcher(void* arg) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting system distributor watcher\n");

    DISTRIBUTOR_ON = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Searching for process to distribute...\n");

        if (!process_queue_is_empty(FE)) {
            Process* p = dequeue_process_queue(FE);

            if (p->priority == SYSTEM_PROCESS_REAL_TIME_PRIORITY) {
                fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FTR\n", p->id);
                p->curentProcessQueueId = FTR_ID;
                enqueue_process_queue(FTR, p);
            }
            else {
                fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FU\n", p->id);
                p->curentProcessQueueId = FU_ID;
                enqueue_process_queue(FU, p);
            }
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system distributor watcher\n");
    printf("Stopping system distributor watcher\n");

    DISTRIBUTOR_ON = false;

    return NULL;
}
