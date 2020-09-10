Process* process_creator(char pr) {
    if (process_created > PROCESS_LIMIT) {
        /*
            TODO: Finish program in this condition
        */
        return NULL;
    }

    return declare_process(process_created+1, pr);
}