void finish_logs() {
    fclose(SYSTEM_TRACKING_OUTPUT);
}


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
    clean_process_queue(FU);
    clean_process_queue(FU2);
    clean_process_queue(FU3);
    clean_process_queue(FTR);
}


void finishers() {
    finish_cpus();
    finish_memory();
    finish_cd_drivers();
    finish_modems();
    finish_printers();
    finish_scanners();
    finish_process_queues();

    fprintf(SYSTEM_TRACKING_OUTPUT, "System finished with success\n");

    finish_logs();
}
