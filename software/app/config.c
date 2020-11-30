/* default libs */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* types */
#include "./types/bool.c"

/* utils */
#include "./utils/sleep-execution.c"
#include "./utils/strings.c"

/* constants */
#include "./constants/system.c"

/* logs */
#include "./resources/system/logs.c"

/* resources */
#include "./resources/process.c"
#include "./resources/process-queue.c"
#include "./resources/cpu.c"
#include "./resources/memory.c"
#include "./resources/memory-task.c"
#include "./resources/memory-task-queue.c"
#include "./resources/peripherals-task.c"
#include "./resources/peripherals-task-queue.c"
#include "./resources/cd-driver.c"
#include "./resources/modem.c"
#include "./resources/printer.c"
#include "./resources/scanner.c"

/* resources.system */
#include "./resources/system/globals.c"
#include "./resources/system/process-queues.c"
#include "./resources/system/dispatcher-watcher.c"
#include "./resources/system/distributor-watcher.c"
#include "./resources/system/memory-task-watcher.c"
#include "./resources/system/peripherals-task-watcher.c"
#include "./resources/system/system-turnoff-watcher.c"
#include "./resources/system/initializers.c"
#include "./resources/system/finishers.c"
#include "./resources/system/process-creator.c"

/* functions */
#include "./functions/read-process-from-file.c"

/* tests */
#include "./tests/process-queue.c"
#include "./tests/memory.c"
#include "./tests/thread.c"
