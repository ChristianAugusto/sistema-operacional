#include "./app/config.c"



int main() {
    initializers();



    /* tests */
    process_creator('3', true);
    process_creator('3', true);
    process_creator('3', true);



    system_turnoff_watcher();



    finishers();



    return 0;
}
