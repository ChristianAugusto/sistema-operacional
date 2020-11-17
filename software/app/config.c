/* default libs */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* types */
#include "./types/bool.c"

/* utils */
#include "./utils/sleep_execution.c"
#include "./utils/strings.c"

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

/* resources.system */
#include "./resources/system/globals.c"
#include "./resources/system/elements/process_queues.c"
#include "./resources/system/elements/watchers.c"
#include "./resources/system/initializers.c"
#include "./resources/system/finishers.c"
#include "./resources/system/process_creator.c"

/* functions */
#include "./functions/read_process_from_file.c"

/* tests */
#include "./tests/process-queue.c"
#include "./tests/memory.c"
#include "./tests/thread.c"
