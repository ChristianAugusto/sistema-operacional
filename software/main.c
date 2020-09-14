#include "./app/config.c"



int main() {
    /* initializers */
    init_process_queues();
    init_memory();
    init_process_created();



    /* tests */
    test_memory();



    /* finishers */
    finish_process_queues();
    finish_memory();

    return 0;
}