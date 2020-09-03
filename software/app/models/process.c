typedef struct process {
    char priority;
    struct process * next;
} Process;



Process* declare_process(char pr) {
    Process* p = (Process*)malloc(sizeof(Process));

    p->priority = pr;

    return p;
}