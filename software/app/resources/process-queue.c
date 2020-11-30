typedef struct {
    Process* head;
    Process* last;
    int size;
} ProcessQueue;



bool process_queue_is_empty(ProcessQueue* q) {
    return q->head == NULL && q->size == 0;
}


ProcessQueue* declare_process_queue() {
    ProcessQueue* q = (ProcessQueue*)malloc(sizeof(ProcessQueue));

    q->head = NULL;
    q->last = NULL;
    q->size = 0;

    return q;
}


void clean_process_queue(ProcessQueue* q) {
    free(q);
}


void enqueue_process_queue(ProcessQueue* q, Process* p) {
    p->next = NULL;

    if (process_queue_is_empty(q)) {
        q->head = p;
    }
    else {
        q->last->next = p;
    }

    q->last = p;
    q->size++;
}


Process* peek_process_queue(ProcessQueue* q) {
    return q->head;
}


Process* dequeue_process_queue(ProcessQueue* q) {
    if (process_queue_is_empty(q)) {
        return NULL;
    }


    Process* aux = q->head;

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



void empty_process_queue(ProcessQueue* q) {
    while (!process_queue_is_empty(q)) {
        dequeue_process_queue(q);
    }
}


void print_process_queue_default_output(ProcessQueue* q) {
    if (process_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    printf("[\n");

    Process* aux = q->head;

    while (aux != NULL) {
        print_process_default_output(aux, "\t", ",");

        aux = aux->next;
    }

    printf("]\n");
}


void print_process_queue_system_tracking_output(ProcessQueue* q) {
    if (process_queue_is_empty(q)) {
        fprintf(SYSTEM_TRACKING_OUTPUT, "[]\n");
        return;
    }


    fprintf(SYSTEM_TRACKING_OUTPUT, "[\n");

    Process* aux = q->head;

    while (aux != NULL) {
        print_process_system_tracking_output(aux, "\t", ",");

        aux = aux->next;
    }

    fprintf(SYSTEM_TRACKING_OUTPUT, "]\n");
}
