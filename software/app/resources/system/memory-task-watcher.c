/**
 * Memory task watcher: Verify if has memory task in MTQ.
 */
void* memory_task_watcher(void* arg) {
    fprintf(SYSTEM_TRACKING_OUTPUT, "Starting memory task watcher\n");

    MEMORY_TASK_WATCHER_ON = true;

    while (SYSTEM_STATUS == SYSTEM_STATUS_NORMAL) {
        if (!memory_task_queue_is_empty(MTQ)) {
            RUNNING_MEMORY_TASK = dequeue_memory_task_queue(MTQ);

            print_memory_task_queue_default_output(MTQ);

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

                    PeripheralsTask* pt = declare_peripherals_task(
                        PERIPHERALS_TASK_DEALLOCATE, str_copy(RUNNING_MEMORY_TASK->processId), 0U,
                        0U, 0U, 0U, true
                    );
                    enqueue_peripherals_task_queue(PTQ, pt);
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

                                PeripheralsTask* pt = declare_peripherals_task(
                                    PERIPHERALS_TASK_DEALLOCATE, str_copy(aux->id), 0U,
                                    0U, 0U, 0U, true
                                );
                                enqueue_peripherals_task_queue(PTQ, pt);

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

            RUNNING_MEMORY_TASK = EMPTY_RUNNING_MEMORY_TASK;
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping memory task watcher\n");
    printf("Stopping memory task watcher\n");

    MEMORY_TASK_WATCHER_ON = false;

    return NULL;
}
