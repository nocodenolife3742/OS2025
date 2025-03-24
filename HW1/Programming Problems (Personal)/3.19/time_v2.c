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

    // create pipe for communication
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "failed to create pipe\n");
        return EXIT_FAILURE;
    }

    // fork the program
    const pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // child process

        // close read end of the pipe
        close(pipefd[0]);

        // get start time
        struct timeval start_time;
        gettimeofday(&start_time, NULL);
        write(pipefd[1], &start_time, sizeof(start_time));
        close(pipefd[1]);

        // execute the command
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "error when executing program\n");
        exit(EXIT_FAILURE);
    } else {
        // parent process

        // close write end of the pipe
        close(pipefd[1]);

        // read start time
        struct timeval start_time, end_time;
        read(pipefd[0], &start_time, sizeof(start_time));
        close(pipefd[0]);

        // wait for child to finish
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child process terminated abnormally\n");
        }

        // get elasped time
        gettimeofday(&end_time, NULL);
        const double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                                    (end_time.tv_usec - start_time.tv_usec) / 1e6;
        printf("Elapsed time: %.5f seconds\n", elapsed_time);
    }

    return 0;
}

