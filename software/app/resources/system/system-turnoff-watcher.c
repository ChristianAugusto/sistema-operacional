/**
 *  System turn off watcher: Verify if is time to turn off system.
 */
void system_turnoff_watcher() {
    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Turn off system ?...\n");


        /*
            Code to force system to turn off
        */
        if (
            process_queue_is_empty(FE) && process_queue_is_empty(FU) &&
            process_queue_is_empty(FU2) && process_queue_is_empty(FU3) &&
            memory_task_queue_is_empty(MTQ) && RUNNING_MEMORY_TASK == EMPTY_RUNNING_MEMORY_TASK &&
            peripherals_task_queue_is_empty(PTQ) && RUNNING_PERIPHERALS_TASK == EMPTY_RUNNING_PERIPHERALS_TASK
        ) {
            unsigned int i, countCPUSProcessing = 0;
            for (i = 0; i < CPUS_TOTAL; i++) {
                if (CPUS[i].running_process != EMPTY_CPU_RUNNING_PROCESS) {
                    countCPUSProcessing++;
                    break;
                }
            }

            if (countCPUSProcessing == 0) {
                printf("Turning off system\n");
                fprintf(SYSTEM_TRACKING_OUTPUT, "Turning off system\n");
                SYSTEM_STATUS = SYSTEM_STATUS_TURNING_OFF;
            }
        }
    }

    unsigned int i, countCPUSOn;
    do {
        for (i = 0, countCPUSOn = 0; i < CPUS_TOTAL; i++) {
            if (CPUS[i].dispatcherOn) {
                countCPUSOn++;
            }
        }

        printf("Waiting watchers turning off...\n");
    } while (countCPUSOn > 0 || DISTRIBUTOR_ON || MEMORY_TASK_WATCHER_ON || PERIPHERALS_TASK_WATCHER_ON);

    fprintf(SYSTEM_TRACKING_OUTPUT, "System turned off\n");
    printf("System turned off\n");
}
