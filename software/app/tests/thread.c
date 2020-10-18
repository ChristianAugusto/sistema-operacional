void* callback(void* vargp) {
    sleep_execution(1000);

    printf("Printing from Thread \n");

    return NULL; 
}

void test_thread() {
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, callback, NULL);
    // pthread_join(thread_id, NULL);
    printf("Sync print\n");
    sleep_execution(1000);
}