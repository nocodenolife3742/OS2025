#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(const int argc, char *argv[]) {
    // check if the number of arguments is correct
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // create shared memory
    const char *shm_name = "/shm_time";
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        fprintf(stderr, "cannot open %s\n", shm_name);
        return EXIT_FAILURE;
    }
    if (ftruncate(shm_fd, sizeof(struct timeval)) == -1) {
        fprintf(stderr, "cannot truncate %s\n", shm_name);
        shm_unlink(shm_name);
        return EXIT_FAILURE;
    }

    // map shared memory
    struct timeval *shared_time = mmap(0, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_time == MAP_FAILED) {
        fprintf(stderr, "cannot mmap %s\n", shm_name);
        return EXIT_FAILURE;
    }

    // fork the program
    const pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        munmap(shared_time, sizeof(struct timeval));
        shm_unlink(shm_name);
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // child process

        // get start time
        struct timeval start_time;
        gettimeofday(&start_time, NULL);
        *shared_time = start_time;

        // execute the command
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "error when executing program\n");
        exit(EXIT_FAILURE);
    } else {
        // parent process

        // wait for child to finish
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child process terminated abnormally\n");
        }

        // get elasped time
        struct timeval end_time;
        gettimeofday(&end_time, NULL);
        const double elapsed_time = (end_time.tv_sec - shared_time->tv_sec) +
                                    (end_time.tv_usec - shared_time->tv_usec) / 1e6;
        printf("Elapsed time: %.5f seconds\n", elapsed_time);

        // cleanup shared memory
        munmap(shared_time, sizeof(struct timeval));
        shm_unlink(shm_name);
    }

    return 0;
}

