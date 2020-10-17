/* default libs */
#include <stdio.h>
#include <stdlib.h>

/* models */
#include "./models/boolean.c"

/* utils */
#include "./utils/sleep_execution.c"

/* constants */
#include "./constants/system.c"

/* resources */
#include "./resources/cpu.c"
#include "./resources/memory.c"
#include "./resources/cd_driver.c"
#include "./resources/modem.c"
#include "./resources/printer.c"
#include "./resources/scanner.c"
#include "./resources/process.c"
#include "./resources/process-queue.c"
#include "./resources/system.c"

/* functions */
#include "./functions/read_process_from_file.c"

/* tests */
#include "./tests/process-queue.c"
#include "./tests/memory.c"
