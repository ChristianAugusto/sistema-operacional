void finish_cpus() {
    free(CPUS);
}


void finish_memory() {
    free(MEMORY);
}


void finish_cd_drivers() {
    free(CD_DRIVERS);
}


void finish_modems() {
    free(MODEMS);
}


void finish_printers() {
    free(PRINTERS);
}


void finish_scanners() {
    free(SCANNERS);
}


void finish_process_queues() {
    clean_process_queue(FE);
    clean_process_queue(UQ);
    clean_process_queue(UQ2);
    clean_process_queue(UQ3);
    clean_process_queue(RTQ);
}


void finishers() {
    finish_cpus();
    finish_memory();
    finish_cd_drivers();
    finish_modems();
    finish_printers();
    finish_scanners();
    finish_process_queues();
}
