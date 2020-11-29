/**
 *  System dispatcher watcher: Verify if has process in FTR or FUs.
 */
void* dispatcher_watcher(void* arg) {
    CPU* cpu = (CPU*)arg;


    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting system dispatcher watcher\n");

    cpu->dispatcherOn = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        Process* p = NULL;

        printf("Searching for process in FTR...\n");
        p = dequeue_process_queue(FTR);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, p->id, p->qtdMemory
            );

            while (mt->success == NULL);


            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);
            if (memory_allocated) {
                sleep_execution(p->processingTime);
                p->processedTime = p->processingTime;
                clean_process(p);
            }
            else {
                /*
                    TODO: Preempção e desalocação
                */
            }

            continue;
        }

        printf("Searching for process in FU...\n");
        p = dequeue_process_queue(FU);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, p->id, p->qtdMemory
            );

            while (mt->success == NULL);

            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                sleep_execution(QUANTUM);
                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    clean_process(p);
                }
                else {
                    enqueue_process_queue(FU2, p);
                }
            }
            else {
                enqueue_process_queue(FU2, p);
            }

            continue;
        }

        printf("Searching for process in FU2...\n");
        p = dequeue_process_queue(FU2);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, p->id, p->qtdMemory
            );

            while (mt->success == NULL);

            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                sleep_execution(QUANTUM);
                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    clean_process(p);
                }
                else {
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                enqueue_process_queue(FU3, p);
            }

            continue;
        }

        printf("Searching for process in FU3...\n");
        p = dequeue_process_queue(FU3);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, p->id, p->qtdMemory
            );

            while (mt->success == NULL);

            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                sleep_execution(QUANTUM);
                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    clean_process(p);
                }
                else {
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                enqueue_process_queue(FU3, p);
            }

            continue;
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system dispatcher watcher\n");

    cpu->dispatcherOn = false;

    return NULL;
}


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
 * Memory task watcher: Verify if has memory task in MTQ.
 */
void* memory_task_watcher(void* arg) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting memory task watcher\n");

    MEMORY_TASK_WATCHER_ON = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Searching memory tasks to execute...\n");

        if (!memory_task_queue_is_empty(MTQ)) {
            MemoryTask* mt = dequeue_memory_task_queue(MTQ);

            if (mt->actionType == MEMORY_TASK_ALLOCATE) {
                bool memory_allocated = allocate_memory(mt->processId, mt->qtdMemory);

                bool* aux = (bool*)malloc(sizeof(bool));
                *aux = memory_allocated;

                if (memory_allocated) {
                    mt->success = aux;
                }
            }
            else if (mt->actionType == MEMORY_TASK_DEALLOCATE) {
                deallocate_memory(mt->processId);
            }
            else if (mt->actionType == MEMORY_TASK_DEALLOCATE_TO_ALLOCATE) {
                /*
                    TODO: Implementar preempção
                */
            }
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping memory task watcher\n");
    printf("Stopping memory task watcher\n");

    MEMORY_TASK_WATCHER_ON = false;

    return NULL;
}


/**
 *  System turn off watcher: Verify if is time to turn off system.
 */
void system_turnoff_watcher() {
    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Turn off system ?...\n");

        printf("Turning off system\n");
        fprintf(SYSTEM_TRACKING_OUTPUT, "Turning off system\n");

        SYSTEM_STATUS = SYSTEM_STATUS_TURNING_OFF;
    }

    unsigned int i, countCPUSOn;
    do {
        for (i = 0, countCPUSOn = 0; i < CPUS_TOTAL; i++) {
            if (CPUS[i].dispatcherOn) {
                countCPUSOn++;
            }
        }

        printf("Waiting watchers turning off...\n");
    } while (countCPUSOn > 0 || DISTRIBUTOR_ON || MEMORY_TASK_WATCHER_ON);

    fprintf(SYSTEM_TRACKING_OUTPUT, "System turned off\n");
    printf("System turned off\n");
}
