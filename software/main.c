#include "./app/config.c"



int main() {
    initializers();



    /* tests */
    // test_thread();


    system_turnoff_watcher();

    finishers();



    return 0;
}
