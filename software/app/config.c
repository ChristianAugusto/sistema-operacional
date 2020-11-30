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

/* logs */
#include "./resources/system/logs.c"

/* resources */
#include "./resources/process.c"
#include "./resources/process-queue.c"
#include "./resources/cpu.c"
#include "./resources/memory.c"
#include "./resources/memory-task.c"
#include "./resources/memory-task-queue.c"
#include "./resources/cd_driver.c"
#include "./resources/modem.c"
#include "./resources/printer.c"
#include "./resources/scanner.c"

/* resources.system */
#include "./resources/system/globals.c"
#include "./resources/system/process_queues.c"
#include "./resources/system/dispatcher_watcher.c"
#include "./resources/system/distributor_watcher.c"
#include "./resources/system/memory_task_watcher.c"
#include "./resources/system/system_turnoff_watcher.c"
#include "./resources/system/initializers.c"
#include "./resources/system/finishers.c"
#include "./resources/system/process_creator.c"

/* functions */
#include "./functions/read_process_from_file.c"

/* tests */
#include "./tests/process-queue.c"
#include "./tests/memory.c"
#include "./tests/thread.c"
