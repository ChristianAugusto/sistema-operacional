void test_process_queue(ProcessQueue* q) {
    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));

    print_process_queue(q);
    printf("--------------------------\n");


    dequeue_process_queue(q);
    dequeue_process_queue(q);


    print_process_queue(q);
    printf("--------------------------\n");


    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));


    print_process_queue(q);
    printf("--------------------------\n");


    dequeue_process_queue(q);
    dequeue_process_queue(q);
    dequeue_process_queue(q);
    dequeue_process_queue(q);


    print_process_queue(q);


    // enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    // enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    // enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
    // enqueue_process_queue(q, declare_process(DEFAULT_PRIORITY));
}