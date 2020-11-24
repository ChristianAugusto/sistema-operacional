void test_memory() {
    allocate_memory("1", 4);
    allocate_memory("2", 8);
    allocate_memory("3", 12);

    deallocate_memory("2");

    allocate_memory("4", 20);
    // allocate_memory("5", 20);

    // deallocate_memory("3");

    print_memory();
}
