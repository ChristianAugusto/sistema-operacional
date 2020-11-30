typedef struct {
    MemoryTask* head;
    MemoryTask* last;
    int size;
} MemoryTaskQueue;



bool memory_task_queue_is_empty(MemoryTaskQueue* q) {
    return q->head == NULL && q->size == 0;
}


MemoryTaskQueue* declare_memory_task_queue() {
    MemoryTaskQueue* q = (MemoryTaskQueue*)malloc(sizeof(MemoryTaskQueue));

    q->head = NULL;
    q->last = NULL;
    q->size = 0;

    return q;
}


void clean_memory_task_queue(MemoryTaskQueue* q) {
    free(q);
}


void enqueue_memory_task_queue(MemoryTaskQueue* q, MemoryTask* mt) {
    mt->next = NULL;

    if (memory_task_queue_is_empty(q)) {
        q->head = mt;
    }
    else {
        q->last->next = mt;
    }

    q->last = mt;
    q->size++;
}


MemoryTask* peek_memory_task_queue(MemoryTaskQueue* q) {
    return q->head;
}


MemoryTask* dequeue_memory_task_queue(MemoryTaskQueue* q) {
    if (memory_task_queue_is_empty(q)) {
        return NULL;
    }


    MemoryTask* aux = q->head;

    if (q->size == 1) {
        q->head = NULL;
        q->last = NULL;
    }
    else {
        q->head = q->head->next;
    }

    q->size--;

    return aux;
}


void clean_memory_tasks(MemoryTask* mt) {
    free(mt);
}


void empty_memory_task_queue(MemoryTaskQueue* q) {
    while (!memory_task_queue_is_empty(q)) {
        dequeue_memory_task_queue(q);
    }
}


void print_memory_task_queue_default_output(MemoryTaskQueue* q) {
    if (memory_task_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    printf("[\n");

    MemoryTask* aux = q->head;

    while (aux != NULL) {
        print_memory_task_default_output(aux, "\t", ",");

        aux = aux->next;
    }

    printf("]\n");
}


void print_memory_task_queue_system_tracking_output(MemoryTaskQueue* q) {
    if (memory_task_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    fprintf(SYSTEM_TRACKING_OUTPUT, "[\n");

    MemoryTask* aux = q->head;

    while (aux != NULL) {
        print_memory_task_system_tracking_output(aux, "\t", ",");

        aux = aux->next;
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "]\n");
}
