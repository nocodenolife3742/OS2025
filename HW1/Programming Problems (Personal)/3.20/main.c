// file to test APIs
#include <stdio.h>
#include "pid_manager.h"

int main() {
    if (allocate_map() == -1) {
        printf("Failed to initialize PID map.\n");
        return 1;
    }

    // allocate some PIDs
    const int pid1 = allocate_pid();
    const int pid2 = allocate_pid();
    printf("Allocated PIDs: %d, %d\n", pid1, pid2);

    // release and reallocate PIDs
    release_pid(pid1);
    const int pid3 = allocate_pid();
    printf("Reallocated PID: %d\n", pid3);

    // free map in the memory
    free_map();

    return 0;
}
