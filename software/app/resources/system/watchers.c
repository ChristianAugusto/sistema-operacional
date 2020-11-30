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
            MemoryTask* mt;

            mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
            );
            enqueue_memory_task_queue(MTQ, mt);

            while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

            if (mt->success == NULL) {
                break;
            }


            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);
            if (memory_allocated) {
                cpu->running_process = p;

                printf("Running process %s\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Running process %s\n", p->id);
                sleep_execution(p->processingTime * SYSTEM_TIME_UNIT);

                cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                );
                enqueue_memory_task_queue(MTQ, mt);

                p->processedTime = p->processingTime;

                printf("Finishing process %s in FTR\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Finishing process %s in FTR\n", p->id);
                clean_process(p);
            }
            else {
                printf("Real time process and system without enough memory to allocate %s\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT,
                    "Real time process and system without enough memory to allocate %s\n", p->id, p->id);

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE_TO_ALLOCATE, str_copy(p->id), p->qtdMemory, false
                );
                enqueue_memory_task_queue(MTQ, mt);

                while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

                if (mt->success == NULL) {
                    break;
                }

                bool memory_allocated = *(mt->success);

                if (memory_allocated) {
                    cpu->running_process = p;

                    printf("Running process after deallocate to allocate %s\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "Running process after deallocate to allocate %s\n", p->id);
                    sleep_execution(p->processingTime * SYSTEM_TIME_UNIT);

                    cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                    mt = declare_memory_task(
                        MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                    );
                    enqueue_memory_task_queue(MTQ, mt);

                    p->processedTime = p->processingTime;

                    printf("Finishing process after deallocate to allocate %s in FTR\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "Finishing process after deallocate to allocate %s in FTR\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("Memory watcher can not deallocate to allocate, resending process %s to FTR\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "Memory watcher can not deallocate to allocate, resending process %s to FTR\n", p->id);
                    enqueue_process_queue(FTR, p);
                }
            }

            continue;
        }

        printf("Searching for process in FU...\n");
        p = dequeue_process_queue(FU);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
            );
            enqueue_memory_task_queue(MTQ, mt);

            while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

            if (mt->success == NULL) {
                break;
            }


            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                cpu->running_process = p;

                printf("Running process %s\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Running process %s\n", p->id);

                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }
                sleep_execution(QUANTUM * SYSTEM_TIME_UNIT);
                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }

                cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                );
                enqueue_memory_task_queue(MTQ, mt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("Finishing process %s in FU\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Finishing process %s in FU\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("Sending process %s to FU2\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FU2\n", p->id);
                    p->curentProcessQueueId = FU2_ID;
                    enqueue_process_queue(FU2, p);
                }
            }
            else {
                printf("Memory lack, resending process %s to FU\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Memory lack, resending process %s to FU\n", p->id);
                enqueue_process_queue(FU, p);
            }

            continue;
        }

        printf("Searching for process in FU2...\n");
        p = dequeue_process_queue(FU2);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
            );
            enqueue_memory_task_queue(MTQ, mt);

            while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

            if (mt->success == NULL) {
                break;
            }


            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                cpu->running_process = p;

                printf("Running process %s\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Running process %s\n", p->id);

                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }
                sleep_execution(QUANTUM * SYSTEM_TIME_UNIT);
                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }

                cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                );
                enqueue_memory_task_queue(MTQ, mt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("Finishing process %s in FU2\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Finishing process %s in FU2\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("Sending process %s to FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Sending process %s to FU3\n", p->id);
                    p->curentProcessQueueId = FU3_ID;
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                printf("Memory lack, resending process %s to FU2\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Memory lack, resending process %s to FU2\n", p->id);
                enqueue_process_queue(FU2, p);
            }

            continue;
        }

        printf("Searching for process in FU3...\n");
        p = dequeue_process_queue(FU3);
        if (p != NULL) {
            MemoryTask* mt = declare_memory_task(
                MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
            );
            enqueue_memory_task_queue(MTQ, mt);

            while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

            if (mt->success == NULL) {
                break;
            }


            bool memory_allocated = *(mt->success);
            clean_memory_task(mt);

            if (memory_allocated) {
                cpu->running_process = p;

                printf("Running process %s\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Running process %s\n", p->id);

                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }
                sleep_execution(QUANTUM * SYSTEM_TIME_UNIT);
                if (cpu->running_process == EMPTY_CPU_RUNNING_PROCESS) {
                    continue;
                }

                cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                );
                enqueue_memory_task_queue(MTQ, mt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("Finishing process %s in FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Finishing process %s in FU3\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("Resending process %s to FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Resending process %s to FU3\n", p->id);
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                printf("Memory lack, resending process %s to FU3\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "Memory lack, resending process %s to FU3\n", p->id);
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


/**
 * Memory task watcher: Verify if has memory task in MTQ.
 */
void* memory_task_watcher(void* arg) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting memory task watcher\n");

    MEMORY_TASK_WATCHER_ON = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        printf("Searching memory tasks to execute...\n");

        if (!memory_task_queue_is_empty(MTQ)) {
            RUNNING_MEMORY_TASK = dequeue_memory_task_queue(MTQ);

            bool autoClean = RUNNING_MEMORY_TASK->autoClean;

            if (RUNNING_MEMORY_TASK->actionType == MEMORY_TASK_ALLOCATE) {
                bool memory_allocated = allocate_memory(RUNNING_MEMORY_TASK->processId, RUNNING_MEMORY_TASK->qtdMemory);

                bool* aux = (bool*)malloc(sizeof(bool));
                *aux = memory_allocated;

                RUNNING_MEMORY_TASK->success = aux;
            }
            else if (RUNNING_MEMORY_TASK->actionType == MEMORY_TASK_DEALLOCATE) {
                deallocate_memory(RUNNING_MEMORY_TASK->processId);
            }
            else if (RUNNING_MEMORY_TASK->actionType == MEMORY_TASK_DEALLOCATE_TO_ALLOCATE) {
                bool memory_allocated = false;

                printf("Another try before preemption\n");
                fprintf(SYSTEM_TRACKING_OUTPUT, "Another try before preemption\n");
                memory_allocated = allocate_memory(RUNNING_MEMORY_TASK->processId, RUNNING_MEMORY_TASK->qtdMemory);

                if (memory_allocated) {
                    printf("Success memory allocated without preemption\n");
                    fprintf(SYSTEM_TRACKING_OUTPUT, "Success memory allocated without preemption\n");

                    bool* aux = (bool*)malloc(sizeof(bool));
                    *aux = memory_allocated;

                    RUNNING_MEMORY_TASK->success = aux;
                }
                else {
                    bool* aux_bool = NULL;
                    Process* aux = NULL;
                    unsigned int i;
                    for (i = 0; i < CPUS_TOTAL; i++) {
                        aux = CPUS[i].running_process;

                        if (
                            aux != EMPTY_CPU_RUNNING_PROCESS &&
                            aux->priority != SYSTEM_PROCESS_REAL_TIME_PRIORITY
                        ) {
                            CPUS[i].running_process = EMPTY_CPU_RUNNING_PROCESS;
                            deallocate_memory(aux->id);

                            memory_allocated = allocate_memory(RUNNING_MEMORY_TASK->processId, RUNNING_MEMORY_TASK->qtdMemory);

                            if (memory_allocated) {
                                aux_bool = (bool*)malloc(sizeof(bool));
                                *aux_bool = memory_allocated;

                                RUNNING_MEMORY_TASK->success = aux_bool;

                                printf("Success memory allocated with preemption\n");
                                fprintf(SYSTEM_TRACKING_OUTPUT, "Success memory allocated with preemption\n");

                                if (aux->curentProcessQueueId == FU_ID) {
                                    enqueue_process_queue(FU, aux);
                                }
                                else if (aux->curentProcessQueueId == FU2_ID) {
                                    enqueue_process_queue(FU2, aux);
                                }
                                else if (aux->curentProcessQueueId == FU3_ID) {
                                    enqueue_process_queue(FU3, aux);
                                }

                                break;
                            }

                            if (aux->curentProcessQueueId == FU_ID) {
                                enqueue_process_queue(FU, aux);
                            }
                            else if (aux->curentProcessQueueId == FU2_ID) {
                                enqueue_process_queue(FU2, aux);
                            }
                            else if (aux->curentProcessQueueId == FU3_ID) {
                                enqueue_process_queue(FU3, aux);
                            }
                        }
                    }

                    if (!memory_allocated) {
                        printf("System memory watcher failed in preemption\n");
                        fprintf(SYSTEM_TRACKING_OUTPUT, "System memory watcher failed in preemption\n");


                        aux_bool = (bool*)malloc(sizeof(bool));
                        *aux_bool = memory_allocated;

                        RUNNING_MEMORY_TASK->success = aux_bool;
                    }
                }
            }

            if (autoClean) {
                clean_memory_task(RUNNING_MEMORY_TASK);
            }

            RUNNING_MEMORY_TASK = NULL;
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


        /*
            Code to force system to turn off
        */
        if (
            process_queue_is_empty(FE) && process_queue_is_empty(FU) &&
            process_queue_is_empty(FU2) && process_queue_is_empty(FU3) &&
            memory_task_queue_is_empty(MTQ) && RUNNING_MEMORY_TASK == EMPTY_RUNNING_MEMORY_TASK
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
    } while (countCPUSOn > 0 || DISTRIBUTOR_ON || MEMORY_TASK_WATCHER_ON);

    fprintf(SYSTEM_TRACKING_OUTPUT, "System turned off\n");
    printf("System turned off\n");
}
