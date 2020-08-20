typedef struct process {
    char priority;
    struct process * next;
} Process;

typedef struct {
    Process* head;
    Process* last;
} ProcessQueue;



ProcessQueue* declare_process_queue() {
    ProcessQueue* q = (ProcessQueue*)malloc(sizeof(ProcessQueue));

    q->head = NULL;
    q->last = NULL;

    return q;
}


Process* declare_process() {
    Process* p = (Process*)malloc(sizeof(Process));

    p->priority = DEFAULT_PRIORITY;

    return p;
}


void add_process_queue(ProcessQueue* q, Process* p) {
    p->next = NULL;

    if (q->head == NULL) {
        q->head = p;
        q->last = p;
    }
    else {
        q->last->next = p;
        q->last = p;
    }
}


Process* get_process_queue(ProcessQueue* q) {
    return q->head;
}


Process* remove_process_queue(ProcessQueue* q) {
    if (q->head == NULL) {
        return NULL;
    }


    Process* p = q->head;

    q->head = q->head->next;

    return p;
}


void print_process(Process* p, char* scape, char* division) {

    printf("%s", scape);

    printf("{\n");

    printf("%s", scape);

    printf("\tpriority: %c\n", p->priority);

    printf("%s", scape);

    printf("}%s\n", division);
}


void print_process_queue(ProcessQueue* q) {
    if (q->head == NULL) {
        printf("[]\n");
    }

    printf("[\n");

    Process* aux = q->head;
    while (aux != NULL) {
        print_process(aux, "\t", ",");

        aux = aux->next;
    }

    printf("]\n");
}