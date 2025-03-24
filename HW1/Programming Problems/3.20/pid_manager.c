#include "pid_manager.h"
#include <stdio.h>
#include <stdlib.h>

static int *pid_map = NULL;

int allocate_map(void) {
    pid_map = (int *) calloc(MAX_PID - MIN_PID + 1, sizeof(int));
    return pid_map == NULL ? -1 : 1;
}

int allocate_pid(void) {
    if (pid_map == NULL)
        return -1;
    for (int i = 0; i <= (MAX_PID - MIN_PID); i++) {
        if (pid_map[i] == 0) {
            pid_map[i] = 1;
            return MIN_PID + i;
        }
    }
    return -1;
}

void release_pid(int pid) {
    if (pid_map == NULL || pid < MIN_PID || pid > MAX_PID) {
        printf("Invalid PID: %d\n", pid);
        return;
    }
    pid_map[pid - MIN_PID] = 0;
}

void free_map(void) {
    if (pid_map == NULL)
        return;
    free(pid_map);
}
