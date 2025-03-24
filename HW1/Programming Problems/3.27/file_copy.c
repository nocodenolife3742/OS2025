#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *source = argv[1];
    const char *destination = argv[2];
    
    struct stat stat_buf;
    if (stat(source, &stat_buf) == -1) {
        fprintf(stderr, "Error: Input file does not exist or cannot be accessed\n");
        return EXIT_FAILURE;
    }
    
    if (S_ISDIR(stat_buf.st_mode)) {
        fprintf(stderr, "Error: Input file is a directory\n");
        return EXIT_FAILURE;
    }
    
    if (S_ISREG(stat_buf.st_mode) == 0) {
        fprintf(stderr, "Error: Input file is not a regular file\n");
        return EXIT_FAILURE;
    }
    
    if (stat(destination, &stat_buf) == 0) {
        char response;
        printf("Warning: Output file already exists. Overwrite? (y/n): ");
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y') {
            printf("Operation aborted.\n");
            return EXIT_FAILURE;
        }
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        fprintf(stderr, "Error: Failed to create pipe\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error: Failed to fork process\n");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        close(pipe_fd[1]);

        int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            fprintf(stderr, "Error: Failed to open destination file %s\n", argv[2]);
            close(pipe_fd[0]);
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0)
            write(output_fd, buffer, bytes_read);

        close(output_fd);
        close(pipe_fd[0]);
    } else {
        close(pipe_fd[0]);

        int input_fd = open(argv[1], O_RDONLY);
        if (input_fd == -1) {
            fprintf(stderr, "Error: Failed to open source file %s\n", argv[1]);
            close(pipe_fd[1]);
            return EXIT_FAILURE;
        }

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0)
            write(pipe_fd[1], buffer, bytes_read);

        close(input_fd);
        close(pipe_fd[1]);
    }

    return EXIT_SUCCESS;
}

