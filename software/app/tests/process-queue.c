void test_process_queue(ProcessQueue* q) {
    enqueue_process_queue(q, process_creator('3', false));
    enqueue_process_queue(q, process_creator('3', false));
    enqueue_process_queue(q, process_creator('3', false));
    enqueue_process_queue(q, process_creator('3', false));

    print_process_queue_default_output(q);
    printf("--------------------------\n");


    dequeue_process_queue(q);
    dequeue_process_queue(q);


    print_process_queue_default_output(q);
    printf("--------------------------\n");


    enqueue_process_queue(q, process_creator('3', false));
    enqueue_process_queue(q, process_creator('3', false));


    print_process_queue_default_output(q);
    printf("--------------------------\n");


    dequeue_process_queue(q);
    dequeue_process_queue(q);
    dequeue_process_queue(q);
    dequeue_process_queue(q);


    print_process_queue_default_output(q);


    // enqueue_process_queue(q, process_creator('3', false));
    // enqueue_process_queue(q, process_creator('3', false));
    // enqueue_process_queue(q, process_creator('3', false));
    // enqueue_process_queue(q, process_creator('3', false));
}
