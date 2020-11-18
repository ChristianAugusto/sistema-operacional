/**
 *  System dispatcher watcher: Verify if has process in FTR or FUs every 1 second.
 */
void* dispatcher_watcher(void* args) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting system dispatcher watcher\n");

    while (SYSTEM_STATUS != SYSTEM_STATUS_ERROR && SYSTEM_STATUS != SYSTEM_STATUS_TURN_OFF) {
        printf("Searching for process...\n");

        /*
            TODO: Dispatcher algorithm
        */
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system dispatcher watcher\n");

    return NULL;
}


/**
 *  System distributor watcher: Verify if has process in FE every 1 second.
 */
void* distributor_watcher(void* args) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting system distributor watcher\n");

    while (SYSTEM_STATUS != SYSTEM_STATUS_ERROR && SYSTEM_STATUS != SYSTEM_STATUS_TURN_OFF) {
        printf("Searching for process to distribute...\n");

        Process* p = dequeue_process_queue(FE);

        if (p->priority == SYSTEM_PROCESS_REAL_TIME_PRIORITY) {
            fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FTR\n", p->id);
            enqueue_process_queue(FTR, p);
        }
        else {
            fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FU\n", p->id);
            enqueue_process_queue(FU, p);
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system distributor watcher\n");

    return NULL;
}


/**
 *  System turn off watcher: Verify if is time to turn off system.
 */
void system_turnoff_watcher() {
    int i = 0;

    while (SYSTEM_STATUS != SYSTEM_STATUS_ERROR && SYSTEM_STATUS != SYSTEM_STATUS_TURN_OFF) {
        printf("Turn off system ?...\n");

        /*
            TODO: System turnoff algorithm
        */

        SYSTEM_STATUS = SYSTEM_STATUS_TURN_OFF;
        sleep_execution(1000);
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "System turned off\n");
}
