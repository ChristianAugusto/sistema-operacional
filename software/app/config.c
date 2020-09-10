/* default libs */
#include <stdio.h>
#include <stdlib.h>

/* models */
#include "./models/boolean.c"
#include "./models/process.c"
#include "./models/process-queue.c"

/* resources */
#include "./resources/memory.c"

/* utils */

/* global */
#include "./global/initializers.c"
#include "./global/validators.c"
#include "./global/finishers.c"

/* functions */
#include "./functions/read_process_from_file.c"

/* tests */
#include "./tests/process-queue.c"
