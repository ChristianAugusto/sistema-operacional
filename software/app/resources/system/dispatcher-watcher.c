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

                printf("%s - Running process\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Running process\n", p->id);
                sleep_execution(p->processingTime * SYSTEM_TIME_UNIT);

                cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                mt = declare_memory_task(
                    MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                );
                enqueue_memory_task_queue(MTQ, mt);

                p->processedTime = p->processingTime;

                printf("%s - Finishing process in FTR\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Finishing process in FTR\n", p->id);
                clean_process(p);
            }
            else {
                printf("%s - Real time process and system without enough memory to allocate\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT,
                    "%s - Real time process and system without enough memory to allocate\n", p->id);

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

                    printf("%s - Running process after deallocate to allocate\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "%s - Running process after deallocate to allocate\n", p->id);
                    sleep_execution(p->processingTime * SYSTEM_TIME_UNIT);

                    cpu->running_process = EMPTY_CPU_RUNNING_PROCESS;

                    mt = declare_memory_task(
                        MEMORY_TASK_DEALLOCATE, str_copy(p->id), 0U, true
                    );
                    enqueue_memory_task_queue(MTQ, mt);

                    p->processedTime = p->processingTime;

                    printf("%s - Finishing process after deallocate to allocate in FTR\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "%s - Finishing process after deallocate to allocate in FTR\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("%s - Memory watcher can not deallocate to allocate, resending process to FTR\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT,
                        "%s - Memory watcher can not deallocate to allocate, resending process to FTR\n", p->id);
                    enqueue_process_queue(FTR, p);
                }
            }

            continue;
        }

        printf("Searching for process in FU...\n");
        p = dequeue_process_queue(FU);
        if (p != NULL) {
            MemoryTask* mt;
            PeripheralsTask* pt;
            bool peripherals_allocated = false;
            bool memory_allocated = false;


            pt = declare_peripherals_task(
                PERIPHERALS_TASK_ALLOCATE, str_copy(p->id), p->qtdPrinters,
                p->qtdScanners, p->qtdModems, p->qtdCds, false
            );
            enqueue_peripherals_task_queue(PTQ, pt);

            while (pt->success == NULL && PERIPHERALS_TASK_WATCHER_ON);

            if (pt->success == NULL) {
                break;
            }

            peripherals_allocated = *(pt->success);
            clean_peripherals_task(pt);


            if (peripherals_allocated) {
                mt = declare_memory_task(
                    MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
                );
                enqueue_memory_task_queue(MTQ, mt);

                while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

                if (mt->success == NULL) {
                    break;
                }


                memory_allocated = *(mt->success);
                clean_memory_task(mt);
            }

            if (peripherals_allocated && memory_allocated) {
                cpu->running_process = p;

                printf("%s - Running process\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Running process\n", p->id);

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

                pt = declare_peripherals_task(
                    PERIPHERALS_TASK_DEALLOCATE, str_copy(p->id), 0U,
                    0U, 0U, 0U, true
                );
                enqueue_peripherals_task_queue(PTQ, pt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("%s - Finishing process in FU\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Finishing process in FU\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("%s - Sending process to FU2\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Sending process to FU2\n", p->id);
                    p->curentProcessQueueId = FU2_ID;
                    enqueue_process_queue(FU2, p);
                }
            }
            else {
                printf("%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                fprintf(SYSTEM_TRACKING_OUTPUT,
                    "%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                enqueue_process_queue(FU, p);
            }

            continue;
        }

        printf("Searching for process in FU2...\n");
        p = dequeue_process_queue(FU2);
        if (p != NULL) {
            MemoryTask* mt;
            PeripheralsTask* pt;
            bool peripherals_allocated = false;
            bool memory_allocated = false;


            pt = declare_peripherals_task(
                PERIPHERALS_TASK_ALLOCATE, str_copy(p->id), p->qtdPrinters,
                p->qtdScanners, p->qtdModems, p->qtdCds, false
            );
            enqueue_peripherals_task_queue(PTQ, pt);

            while (pt->success == NULL && PERIPHERALS_TASK_WATCHER_ON);

            if (pt->success == NULL) {
                break;
            }

            peripherals_allocated = *(pt->success);
            clean_peripherals_task(pt);


            if (peripherals_allocated) {
                mt = declare_memory_task(
                    MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
                );
                enqueue_memory_task_queue(MTQ, mt);

                while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

                if (mt->success == NULL) {
                    break;
                }


                memory_allocated = *(mt->success);
                clean_memory_task(mt);
            }

            if (peripherals_allocated && memory_allocated) {
                cpu->running_process = p;

                printf("%s - Running process\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Running process\n", p->id);

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

                pt = declare_peripherals_task(
                    PERIPHERALS_TASK_DEALLOCATE, str_copy(p->id), 0U,
                    0U, 0U, 0U, true
                );
                enqueue_peripherals_task_queue(PTQ, pt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("%s - Finishing process in FU2\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Finishing process in FU2\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("%s - Sending process to FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Sending process to FU3\n", p->id);
                    p->curentProcessQueueId = FU3_ID;
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                printf("%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                fprintf(SYSTEM_TRACKING_OUTPUT,
                    "%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                enqueue_process_queue(FU, p);
            }

            continue;
        }

        printf("Searching for process in FU3...\n");
        p = dequeue_process_queue(FU3);
        if (p != NULL) {
            MemoryTask* mt;
            PeripheralsTask* pt;
            bool peripherals_allocated = false;
            bool memory_allocated = false;


            pt = declare_peripherals_task(
                PERIPHERALS_TASK_ALLOCATE, str_copy(p->id), p->qtdPrinters,
                p->qtdScanners, p->qtdModems, p->qtdCds, false
            );
            enqueue_peripherals_task_queue(PTQ, pt);

            while (pt->success == NULL && PERIPHERALS_TASK_WATCHER_ON);

            if (pt->success == NULL) {
                break;
            }

            peripherals_allocated = *(pt->success);
            clean_peripherals_task(pt);


            if (peripherals_allocated) {
                mt = declare_memory_task(
                    MEMORY_TASK_ALLOCATE, str_copy(p->id), p->qtdMemory, false
                );
                enqueue_memory_task_queue(MTQ, mt);

                while (mt->success == NULL && MEMORY_TASK_WATCHER_ON);

                if (mt->success == NULL) {
                    break;
                }


                memory_allocated = *(mt->success);
                clean_memory_task(mt);
            }

            if (peripherals_allocated && memory_allocated) {
                cpu->running_process = p;

                printf("%s - Running process\n", p->id);
                fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Running process\n", p->id);

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

                pt = declare_peripherals_task(
                    PERIPHERALS_TASK_DEALLOCATE, str_copy(p->id), 0U,
                    0U, 0U, 0U, true
                );
                enqueue_peripherals_task_queue(PTQ, pt);

                p->processedTime += QUANTUM;

                if (p->processedTime >= p->processingTime) {
                    printf("%s - Finishing process in FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Finishing process in FU3\n", p->id);
                    clean_process(p);
                }
                else {
                    printf("%s - Resending process to FU3\n", p->id);
                    fprintf(SYSTEM_TRACKING_OUTPUT, "%s - Resending process to FU3\n", p->id);
                    enqueue_process_queue(FU3, p);
                }
            }
            else {
                printf("%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                fprintf(SYSTEM_TRACKING_OUTPUT,
                    "%s - Memory lack %d || peripherals not available %d, resending process to FU\n",
                    p->id, memory_allocated, peripherals_allocated);
                enqueue_process_queue(FU, p);
            }

            continue;
        }
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "Stopping system dispatcher watcher\n");

    cpu->dispatcherOn = false;

    return NULL;
}
