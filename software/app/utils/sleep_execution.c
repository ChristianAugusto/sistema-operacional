#ifdef _WIN32
    #include <windows.h>

    void sleep_execution(unsigned milliseconds) {
        // windows
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep_execution(unsigned milliseconds) {
        // unix
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif
