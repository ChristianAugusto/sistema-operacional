void init_logs() {
    SYSTEM_TRACKING_OUTPUT = fopen("./app/logs/system-tracking.log", "w");
}


void init_cpus() {
    CPUS = (CPU*)malloc(CPUS_TOTAL * sizeof(CPU));

    unsigned int i;
    for (i = 0; i < CPUS_TOTAL; i++) {
        CPUS[i].running_process = EMPTY_CPU_RUNNING_PROCESS;
        pthread_create(&CPUS[i].dispatcher_thread_id, NULL, dispatcher_watcher, &CPUS[i]);
    }
}


void init_memory() {
    MEMORY = (MemoryPosition*)malloc(SYSTEM_MEMORY_TOTAL * sizeof(MemoryPosition));

    unsigned long long int i;
    for (i = 0; i < SYSTEM_MEMORY_TOTAL; i++) {
        MEMORY[i].processId = NULL;
    }

    MEMORY_USED = 0;
}


void init_cd_drivers() {
    CD_DRIVERS = (CD_DRIVER*)malloc(CD_DRIVERS_TOTAL * sizeof(CD_DRIVER));

    unsigned i;
    for (i = 0; i < CD_DRIVERS_TOTAL; i++) {
        CD_DRIVERS[i].processId = NULL;
    }
}


void init_modems() {
    MODEMS = (MODEM*)malloc(MODEMS_TOTAL * sizeof(MODEM));

    unsigned i;
    for (i = 0; i < MODEMS_TOTAL; i++) {
        MODEMS[i].processId = NULL;
    }
}


void init_printers() {
    PRINTERS = (PRINTER*)malloc(PRINTERS_TOTAL * sizeof(PRINTER));

    unsigned i;
    for (i = 0; i < PRINTERS_TOTAL; i++) {
        PRINTERS[i].processId = NULL;
    }
}


void init_scanners() {
    SCANNERS = (SCANNER*)malloc(SCANNERS_TOTAL * sizeof(SCANNER));

    unsigned i;
    for (i = 0; i < SCANNERS_TOTAL; i++) {
        SCANNERS[i].processId = NULL;
    }
}


void init_process_queues() {
    FE = declare_process_queue();
    FU = declare_process_queue();
    FU2 = declare_process_queue();
    FU3 = declare_process_queue();
    FTR = declare_process_queue();
}


void init_distributor_watcher() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, distributor_watcher, NULL);
}


void init_process_created() {
    PROCESS_CREATED = (char*)malloc(2*sizeof(char));
    PROCESS_CREATED[0] = '0';
    PROCESS_CREATED[1] = '\0';
}


void init_system_status() {
    SYSTEM_STATUS = SYSTEM_STATUS_NORMAL;
}


void init_running_memory_task() {
    RUNNING_MEMORY_TASK = EMPTY_RUNNING_MEMORY_TASK;
}


void init_memory_tasks_queue() {
    MTQ = declare_memory_task_queue();
}


void init_memory_task_watcher() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, memory_task_watcher, NULL);
}


void init_running_peripherals_task() {
    RUNNING_PERIPHERALS_TASK = EMPTY_RUNNING_PERIPHERALS_TASK;
}


void init_peripherals_tasks_queue() {
    PTQ = declare_peripherals_task_queue();
}


void init_peripherals_task_watcher() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, peripherals_task_watcher, NULL);
}


void initializers() {
    init_logs();
    init_memory();
    init_modems();
    init_cd_drivers();
    init_scanners();
    init_printers();
    init_process_created();
    init_process_queues();
    init_running_memory_task();
    init_memory_tasks_queue();
    init_memory_task_watcher();
    init_running_peripherals_task();
    init_peripherals_tasks_queue();
    init_peripherals_task_watcher();
    init_cpus();
    init_distributor_watcher();
    init_system_status();

    printf("System initialized with success\n");
    fprintf(SYSTEM_TRACKING_OUTPUT, "System initialized with success\n");
}
