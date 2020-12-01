typedef struct {
    PeripheralsTask* head;
    PeripheralsTask* last;
    int size;
} PeripheralsTaskQueue;



bool peripherals_task_queue_is_empty(PeripheralsTaskQueue* q) {
    return q->head == NULL && q->size == 0;
}


PeripheralsTaskQueue* declare_peripherals_task_queue() {
    PeripheralsTaskQueue* q = (PeripheralsTaskQueue*)malloc(sizeof(PeripheralsTaskQueue));

    q->head = NULL;
    q->last = NULL;
    q->size = 0;

    return q;
}


void clean_peripherals_task_queue(PeripheralsTaskQueue* q) {
    free(q);
}


void enqueue_peripherals_task_queue(PeripheralsTaskQueue* q, PeripheralsTask* pt) {
    pt->next = NULL;

    if (peripherals_task_queue_is_empty(q)) {
        q->head = pt;
    }
    else {
        q->last->next = pt;
    }

    q->last = pt;
    q->size++;
}


PeripheralsTask* peek_peripherals_task_queue(PeripheralsTaskQueue* q) {
    return q->head;
}


PeripheralsTask* dequeue_peripherals_task_queue(PeripheralsTaskQueue* q) {
    if (peripherals_task_queue_is_empty(q)) {
        return NULL;
    }


    PeripheralsTask* aux = q->head;

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



void empty_peripherals_task_queue(PeripheralsTaskQueue* q) {
    while (!peripherals_task_queue_is_empty(q)) {
        dequeue_peripherals_task_queue(q);
    }
}


void print_peripherals_task_queue_default_output(PeripheralsTaskQueue* q) {
    if (peripherals_task_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    printf("[\n");

    PeripheralsTask* aux = q->head;

    while (aux != NULL) {
        print_peripherals_task_default_output(aux, "\t", ",");

        aux = aux->next;
    }

    printf("]\n");
}


void print_peripherals_task_queue_system_tracking_output(PeripheralsTaskQueue* q) {
    if (peripherals_task_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    fprintf(SYSTEM_TRACKING_OUTPUT, "[\n");

    PeripheralsTask* aux = q->head;

    while (aux != NULL) {
        print_peripherals_task_system_tracking_output(aux, "\t", ",");

        aux = aux->next;
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "]\n");
}
