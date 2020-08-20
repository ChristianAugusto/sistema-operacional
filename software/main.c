#include "./app/config.c"



int main() {
    ProcessQueue* q = declare_process_queue();


    add_process_queue(q, declare_process());
    add_process_queue(q, declare_process());
    add_process_queue(q, declare_process());
    add_process_queue(q, declare_process());

    print_process_queue(q);

    return 0;
}