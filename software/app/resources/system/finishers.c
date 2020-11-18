void finish_logs() {
    fclose(SYSTEM_TRACKING_OUTPUT);
}


void finish_cpus() {
    free(CPUS);
    CPUS = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "CPUS finished\n");
}


void finish_memory() {
    free(MEMORY);
    MEMORY = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "MEMORY finished\n");
}


void finish_cd_drivers() {
    free(CD_DRIVERS);
    CD_DRIVERS = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "CD_DRIVERS finished\n");
}


void finish_modems() {
    free(MODEMS);
    MODEMS = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "MODEMS finished\n");
}


void finish_printers() {
    free(PRINTERS);
    PRINTERS = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "PRINTERS finished\n");
}


void finish_scanners() {
    free(SCANNERS);
    SCANNERS = NULL;
    fprintf(SYSTEM_TRACKING_OUTPUT, "SCANNERS finished\n");
}


void finish_process_queues() {
    empty_process_queue(FE);
    clean_process_queue(FE);
    FE = NULL;

    empty_process_queue(FU);
    clean_process_queue(FU);
    FU = NULL;

    empty_process_queue(FU2);
    clean_process_queue(FU2);
    FU2 = NULL;

    empty_process_queue(FU3);
    clean_process_queue(FU3);
    FU3 = NULL;

    empty_process_queue(FTR);
    clean_process_queue(FTR);
    FTR = NULL;

    fprintf(SYSTEM_TRACKING_OUTPUT, "process_queues finished\n");
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
