typedef struct {
    Process* head;
    Process* last;
    int size;
} ProcessQueue;



boolean empty_process_queue(ProcessQueue* q) {
    return !q->head;
}


ProcessQueue* declare_process_queue() {
    ProcessQueue* q = (ProcessQueue*)malloc(sizeof(ProcessQueue));

    q->head = NULL;
    q->last = NULL;
    q->size = 0;

    return q;
}


void enqueue_process_queue(ProcessQueue* q, Process* p) {
    p->next = NULL;

    if (empty_process_queue(q)) {
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


void dequeue_process_queue(ProcessQueue* q) {
    if (empty_process_queue(q)) {
        return;
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

    free(aux);
}


void print_process(Process* p, char* scape, char* division) {

    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tpriority: %c\n", p->priority);

    printf("%s", scape);

    printf("}%s\n", division);
}


void clean_process_queue(ProcessQueue* q) {
    while (!empty_process_queue(q)) {
        dequeue_process_queue(q);
    }
}


void print_process_queue(ProcessQueue* q) {
    if (empty_process_queue(q)) {
        printf("[]\n");
        return;
    }


    printf("[\n");

    Process* aux = q->head;

    while (aux != NULL) {
        print_process(aux, "\t", ",");

        aux = aux->next;
    }

    printf("]\n");
}
