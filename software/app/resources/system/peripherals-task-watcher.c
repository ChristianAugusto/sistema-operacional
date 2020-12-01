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


            if (RUNNING_PERIPHERALS_TASK->actionType == PERIPHERALS_TASK_ALLOCATE) {
                printf("%s - Starting allocating peripherals\n", RUNNING_PERIPHERALS_TASK->processId);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Starting allocating peripherals\n", RUNNING_PERIPHERALS_TASK->processId);

                bool success = true;


                if (RUNNING_PERIPHERALS_TASK->qtdCds > 0) {
                    unsigned int i, cdDriversAvailable = 0;
                    for (i = 0; i < CD_DRIVERS_TOTAL; i++) {
                        if (CD_DRIVERS[i].processId == NULL) {
                            cdDriversAvailable++;
                        }
                    }

                    if (cdDriversAvailable < RUNNING_PERIPHERALS_TASK->qtdCds) {
                        printf("%s - CD Drivers qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);
                        fprintf(SYSTEM_TRACKING_OUTPUT, "%s - CD Drivers qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);

                        bool* aux = (bool*)malloc(sizeof(bool));
                        *aux = false;
                        success = false;

                        RUNNING_PERIPHERALS_TASK->success = aux;
                    }
                }

                if (success && RUNNING_PERIPHERALS_TASK->qtdModems > 0) {
                    unsigned int i, modemsAvailable = 0;
                    for (i = 0; i < MODEMS_TOTAL; i++) {
                        if (MODEMS[i].processId == NULL) {
                            modemsAvailable++;
                        }
                    }

                    if (success && modemsAvailable < RUNNING_PERIPHERALS_TASK->qtdModems) {
                        printf("%s - Modems qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);
                        fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Modems qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);

                        bool* aux = (bool*)malloc(sizeof(bool));
                        *aux = false;
                        success = false;

                        RUNNING_PERIPHERALS_TASK->success = aux;
                    }
                }

                if (success && RUNNING_PERIPHERALS_TASK->qtdPrinters > 0) {
                    unsigned int i, printersAvailable = 0;
                    for (i = 0; i < PRINTERS_TOTAL; i++) {
                        if (PRINTERS[i].processId == NULL) {
                            printersAvailable++;
                        }
                    }

                    if (printersAvailable < RUNNING_PERIPHERALS_TASK->qtdPrinters) {
                        printf("%s - Printers qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);
                        fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Printers qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);

                        bool* aux = (bool*)malloc(sizeof(bool));
                        *aux = false;
                        success = false;

                        RUNNING_PERIPHERALS_TASK->success = aux;
                    }
                }

                if (success && RUNNING_PERIPHERALS_TASK->qtdScanners > 0) {
                    unsigned int i, scannersAvailable = 0;
                    for (i = 0; i < SCANNERS_TOTAL; i++) {
                        if (SCANNERS[i].processId == NULL) {
                            scannersAvailable++;
                        }
                    }

                    if (scannersAvailable < RUNNING_PERIPHERALS_TASK->qtdScanners) {
                        printf("%s - Scanners qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);
                        fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Scanners qtd not available\n",
                            RUNNING_PERIPHERALS_TASK->processId);

                        bool* aux = (bool*)malloc(sizeof(bool));
                        *aux = false;
                        success = false;

                        RUNNING_PERIPHERALS_TASK->success = aux;
                    }
                }



                if (success) {
                    unsigned int i, qtdAllocated;

                    printf("%s - All required peripherals qtd are available\n",
                        RUNNING_PERIPHERALS_TASK->processId);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - All required peripherals qtd are available\n",
                        RUNNING_PERIPHERALS_TASK->processId);

                    for (
                        i = 0, qtdAllocated = 0;
                        i < CD_DRIVERS_TOTAL && qtdAllocated < RUNNING_PERIPHERALS_TASK->qtdCds;
                        i++
                    ) {
                        if (CD_DRIVERS[i].processId == NULL) {
                            CD_DRIVERS[i].processId = str_copy(RUNNING_PERIPHERALS_TASK->processId);
                        }
                    }

                    for (
                        i = 0, qtdAllocated = 0;
                        i < MODEMS_TOTAL && qtdAllocated < RUNNING_PERIPHERALS_TASK->qtdModems;
                        i++
                    ) {
                        if (MODEMS[i].processId == NULL) {
                            MODEMS[i].processId = str_copy(RUNNING_PERIPHERALS_TASK->processId);
                        }
                    }

                    for (
                        i = 0, qtdAllocated = 0;
                        i < PRINTERS_TOTAL && qtdAllocated < RUNNING_PERIPHERALS_TASK->qtdPrinters;
                        i++
                    ) {
                        if (PRINTERS[i].processId == NULL) {
                            PRINTERS[i].processId = str_copy(RUNNING_PERIPHERALS_TASK->processId);
                        }
                    }

                    for (
                        i = 0, qtdAllocated = 0;
                        i < SCANNERS_TOTAL && qtdAllocated < RUNNING_PERIPHERALS_TASK->qtdScanners;
                        i++
                    ) {
                        if (SCANNERS[i].processId == NULL) {
                            SCANNERS[i].processId = str_copy(RUNNING_PERIPHERALS_TASK->processId);
                        }
                    }



                    bool* aux = (bool*)malloc(sizeof(bool));
                    *aux = true;

                    RUNNING_PERIPHERALS_TASK->success = aux;
                }
                else {
                    printf("%s - Can not allocate all required peripherals qtd\n",
                        RUNNING_PERIPHERALS_TASK->processId);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Can not allocate all required peripherals qtd\n",
                        RUNNING_PERIPHERALS_TASK->processId);
                }
            }
            else if (RUNNING_PERIPHERALS_TASK->actionType == PERIPHERALS_TASK_DEALLOCATE) {
                unsigned int i;


                for (i = 0; i < CD_DRIVERS_TOTAL; i++) {
                    if (str_equals(CD_DRIVERS[i].processId, RUNNING_PERIPHERALS_TASK->processId)) {
                        CD_DRIVERS[i].processId = NULL;
                    }
                }

                for (i = 0; i < MODEMS_TOTAL; i++) {
                    if (str_equals(MODEMS[i].processId, RUNNING_PERIPHERALS_TASK->processId)) {
                        MODEMS[i].processId = NULL;
                    }
                }

                for (i = 0; i < PRINTERS_TOTAL; i++) {
                    if (str_equals(PRINTERS[i].processId, RUNNING_PERIPHERALS_TASK->processId)) {
                        PRINTERS[i].processId = NULL;
                    }
                }

                for (i = 0; i < SCANNERS_TOTAL; i++) {
                    if (str_equals(SCANNERS[i].processId, RUNNING_PERIPHERALS_TASK->processId)) {
                        SCANNERS[i].processId = NULL;
                    }
                }
            }


            if (autoClean) {
                clean_peripherals_task(RUNNING_PERIPHERALS_TASK);
            }

            RUNNING_PERIPHERALS_TASK = EMPTY_RUNNING_PERIPHERALS_TASK;
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping peripherals task watcher\n");
    printf("Stopping peripherals task watcher\n");

    PERIPHERALS_TASK_WATCHER_ON = false;

    return NULL;
}
