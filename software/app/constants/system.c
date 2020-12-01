#define SYSTEM_PROCESS_REAL_TIME_PRIORITY '0'
#define SYSTEM_MEMORY_SCALE 1
#define SYSTEM_MEMORY_TOTAL 1024
// #define SYSTEM_MEMORY_TOTAL 1048576 // 1048576 bytes = 1024 mega bytes
#define SYSTEM_STATUS_NORMAL 0
#define SYSTEM_STATUS_TURNING_OFF 1
#define SYSTEM_STATUS_FINISHED 2
#define SYSTEM_STATUS_TURNED_OFF 3
#define SYSTEM_STATUS_ERROR 4
#define SYSTEM_TIME_UNIT 1000 // Seconds

#define CPUS_TOTAL 4
#define EMPTY_CPU_RUNNING_PROCESS NULL
#define EMPTY_RUNNING_MEMORY_TASK NULL
#define PRINTERS_TOTAL 2
#define SCANNERS_TOTAL 1
#define MODEMS_TOTAL 1
#define CD_DRIVERS_TOTAL 2

#define MEMORY_TASK_ALLOCATE 1
#define MEMORY_TASK_DEALLOCATE 2
#define MEMORY_TASK_DEALLOCATE_TO_ALLOCATE 3

#define PERIPHERALS_TASK_ALLOCATE 1
#define PERIPHERALS_TASK_DEALLOCATE 2

#define QUANTUM 2U

#define FTR_ID 0
#define FU_ID 1
#define FU2_ID 2
#define FU3_ID 3
