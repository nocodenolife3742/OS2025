# 3.27 Problem Statement

## Task

Design a file-copying program named `filecopy` using ordinary pipes. This program will be passed two parameters: the name of the file to be copied, and the name of the copied file. The program will then:

1. Create an ordinary pipe.
2. Write the contents of the file to be copied to the pipe.
3. The child process will read this file from the pipe and write it to the destination file.

## Example

If we invoke the program as follows:

```bash
filecopy input.txt copy.txt
```

The file `input.txt` will be written to the pipe. The child process will read the contents of this file and write it to the destination file `copy.txt`.

## Implementation Notes

You may write this program using either UNIX or Windows pipes.

### Steps

1. **Parent Process**:
   - Open the source file (`input.txt`) for reading.
   - Create a pipe.
   - Write the contents of the source file to the pipe.

2. **Child Process**:
   - Read from the pipe.
   - Open the destination file (`copy.txt`) for writing.
   - Write the data read from the pipe to the destination file.

This approach ensures that the file contents are transferred using inter-process communication.
