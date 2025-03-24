#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(const int argc, char **argv) {
    // check if the number of arguments is correct
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // define input and output file paths
    const char *source = argv[1];
    const char *destination = argv[2];

    // Check if the input file exists
    struct stat stat_buf;
    if (stat(source, &stat_buf) == -1) {
        fprintf(stderr, "Error: Input file does not exist or cannot be accessed\n");
        return EXIT_FAILURE;
    }

    // Check if input is a directory
    if (S_ISDIR(stat_buf.st_mode)) {
        fprintf(stderr, "Error: Input file is a directory\n");
        return EXIT_FAILURE;
    }

    // Check if input is a regular file
    if (S_ISREG(stat_buf.st_mode) == 0) {
        fprintf(stderr, "Error: Input file is not a regular file\n");
        return EXIT_FAILURE;
    }

    // Check if the output file exists
    if (stat(destination, &stat_buf) == 0) {
        char response;
        printf("Warning: Output file already exists. Overwrite? (y/n): ");
        scanf(" %c", &response);
        if (response != 'y' && response != 'Y') {
            printf("Operation aborted.\n");
            return EXIT_FAILURE;
        }
    }

    // Open input file
    const int input_fd = open(source, O_RDONLY);
    if (input_fd == -1) {
        fprintf(stderr, "Error: Can not open source file\n");
        return EXIT_FAILURE;
    }

    // Open output file (create if not exist, overwrite if exists)
    const int output_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        fprintf(stderr, "Error: Can not open output file\n");
        close(input_fd);
        return EXIT_FAILURE;
    }

    // Copy content
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        const ssize_t bytes_written = write(output_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error: Can not write to output file\n");
            close(input_fd);
            close(output_fd);
            return EXIT_FAILURE;
        }
    }

    // Check if there was an error while reading
    if (bytes_read == -1) {
        fprintf(stderr, "Error: Can not read from input file\n");
        close(input_fd);
        close(output_fd);
        return EXIT_FAILURE;
    }

    // Close files
    close(input_fd);
    close(output_fd);

    printf("File copied successfully.\n");
    return EXIT_SUCCESS;
}

