#include "./app/config.c"



int main() {
    initializers();



    /* tests */
    read_process_from_file();



    system_turnoff_watcher();



    finishers();



    return 0;
}
