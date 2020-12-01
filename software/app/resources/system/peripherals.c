void print_peripherals_default_output() {
    unsigned int i;

    printf("CD_DRIVERS: [");
    for (i = 0; i < CD_DRIVERS_TOTAL; i++) {
        printf("%s,", CD_DRIVERS[i].processId);
    }
    printf("]\n");

    printf("MODEMS: [");
    for (i = 0; i < MODEMS_TOTAL; i++) {
        printf("%s,", MODEMS[i].processId);
    }
    printf("]\n");

    printf("PRINTERS: [");
    for (i = 0; i < PRINTERS_TOTAL; i++) {
        printf("%s,", PRINTERS[i].processId);
    }
    printf("]\n");

    printf("SCANNERS: [");
    for (i = 0; i < SCANNERS_TOTAL; i++) {
        printf("%s,", SCANNERS[i].processId);
    }
    printf("]\n");
}