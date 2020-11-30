/**
 * Peripherals task watcher: Verify if has peripherals tasks in PTQ.
 */
void* peripherals_task_watcher(void* arg) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting peripherals task watcher\n");

    PERIPHERALS_TASK_WATCHER_ON = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Searching peripherals tasks to execute...\n");

        if (!peripherals_task_queue_is_empty(PTQ)) {
            RUNNING_PERIPHERALS_TASK = dequeue_peripherals_task_queue(PTQ);

            bool autoClean = RUNNING_PERIPHERALS_TASK->autoClean;

            

            if (autoClean) {
                clean_peripherals_task(RUNNING_PERIPHERALS_TASK);
            }

            RUNNING_PERIPHERALS_TASK = NULL;
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping peripherals task watcher\n");
    printf("Stopping peripherals task watcher\n");

    PERIPHERALS_TASK_WATCHER_ON = false;

    return NULL;
}
