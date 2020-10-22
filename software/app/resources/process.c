typedef struct process {
    char* id;
    char priority;
    struct process * next;
} Process;



/**
 *  Process declare. Do not call this function directly.
 *  To create process, use process_creator.
 */
Process* declare_process(char* id, char pr) {
    Process* p = (Process*)malloc(sizeof(Process));

    p->id = id;
    p->priority = pr;

    return p;
}
