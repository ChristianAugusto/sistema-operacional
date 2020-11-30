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
