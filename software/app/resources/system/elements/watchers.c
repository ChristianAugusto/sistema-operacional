/**
 *  System dispatcher watcher: Verify if has process in FTR or FUs every 1 second.
 */
void* dispatcher_watcher(void* arg) {
    CPU* cpu = (CPU*)arg;


    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting system dispatcher watcher\n");

    cpu->dispatcherOn = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Searching for process...\n");

        /*
            TODO: Dispatcher algorithm
        */
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system dispatcher watcher\n");

    cpu->dispatcherOn = false;

    return NULL;
}


/**
 *  System distributor watcher: Verify if has process in FE every 1 second.
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
                enqueue_process_queue(FTR, p);
            }
            else {
                fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FU\n", p->id);
                enqueue_process_queue(FU, p);
            }
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system distributor watcher\n");
    printf("Stopping system distributor watcher\n");

    DISTRIBUTOR_ON = false;

    return NULL;
}


/**
 *  System turn off watcher: Verify if is time to turn off system.
 */
void system_turnoff_watcher() {
    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Turn off system ?...\n");

        printf("Desligando o sistema\n");
        fprintf(SYSTEM_TRACKING_OUTPUT, "Desligando o sistema\n");

        SYSTEM_STATUS = SYSTEM_STATUS_TURNING_OFF;
    }

    unsigned int i, countCPUSOn;
    do {
        for (i = 0, countCPUSOn = 0; i < CPUS_TOTAL; i++) {
            if (CPUS[i].dispatcherOn) {
                countCPUSOn++;
            }
        }

        printf("Esperando watchers desligarem...\n");
    } while (countCPUSOn > 0 || DISTRIBUTOR_ON);

    fprintf(SYSTEM_TRACKING_OUTPUT, "System turned off\n");
}
