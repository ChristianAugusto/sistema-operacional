/**
 *  System dispatcher watcher: Verify if has process in FTR or FUs every 1 second.
 */
void* dispatcher_watcher(void* args) {
    while (SYSTEM_STATUS != SYSTEM_STATUS_ERROR && SYSTEM_STATUS != SYSTEM_STATUS_TURN_OFF) {
        printf("Searching for process...\n");

        /*
            TODO: Dispatcher algorithm
        */

        sleep_execution(1000);
    }

    printf("Stopping system dispatcher watcher\n");

    return NULL;
}


/**
 *  System distributor watcher: Verify if has process in FE every 1 second.
 */
void* distributor_watcher(void* args) {
    while (SYSTEM_STATUS != SYSTEM_STATUS_ERROR && SYSTEM_STATUS != SYSTEM_STATUS_TURN_OFF) {
        printf("Searching for process to distribute...\n");

        /*
            TODO: Distributor algorithm
        */

        sleep_execution(1000);
    }

    printf("Stopping system distributor watcher\n");

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

        if (++i == 10) {
            SYSTEM_STATUS = SYSTEM_STATUS_TURN_OFF;
            sleep_execution(1500);
            break;
        }

        sleep_execution(1000);
    }

    printf("System turned off\n");
}
