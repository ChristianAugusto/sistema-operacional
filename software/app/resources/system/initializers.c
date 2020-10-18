void init_cpus() {
    CPUS = (CPU*)malloc(CPUS_TOTAL * sizeof(CPU));
}


void init_memory() {
    MEMORY = (MemoryPosition*)malloc(SYSTEM_MEMORY_TOTAL * sizeof(MemoryPosition));
    MEMORY_USED = 0;
}


void init_cd_drivers() {
    CD_DRIVERS = (CD_DRIVER*)malloc(CD_DRIVERS_TOTAL * sizeof(CD_DRIVER));
}


void init_modems() {
    MODEMS = (MODEM*)malloc(MODEMS_TOTAL * sizeof(MODEM));
}


void init_printers() {
    PRINTERS = (PRINTER*)malloc(PRINTERS_TOTAL * sizeof(PRINTER));
}


void init_scanners() {
    SCANNERS = (SCANNER*)malloc(SCANNERS_TOTAL * sizeof(SCANNER));
}


void init_process_queues() {
    FE = declare_process_queue();
    UQ = declare_process_queue();
    UQ2 = declare_process_queue();
    UQ3 = declare_process_queue();
    RTQ = declare_process_queue();
}


void init_dispatcher_watcher() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, dispatcher_watcher, NULL);
}


void init_distributor_watcher() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, distributor_watcher, NULL);
}


void init_process_created() {
    PROCESS_CREATED = 0;
}


void initializers() {
    init_cpus();
    init_memory();
    init_cd_drivers();
    init_modems();
    init_printers();
    init_scanners();
    init_process_queues();
    init_process_created();
    init_dispatcher_watcher();
    init_distributor_watcher();
}
