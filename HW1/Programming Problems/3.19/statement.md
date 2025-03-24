# 3.19 Problem Statement

Write a C program called `time.c` that determines the amount of time necessary to run a command from the command line. 

## Usage
```sh
./time <command>
```
This program will report the amount of elapsed time to run the specified command.

## Implementation Details
- This will involve using `fork()` and `exec()` functions, as well as the `gettimeofday()` function to determine the elapsed time.
- It will also require the use of two different IPC mechanisms.

## IPC Mechanisms
### Version 1: POSIX Shared Memory
- The child process writes the starting time to a region of shared memory before calling `exec()`.
- After the child process terminates, the parent reads the starting time from shared memory.
- Refer to Section 3.7.1 for details on using POSIX shared memory.

### Version 2: Pipe
- The child process writes the starting time to the pipe.
- The parent reads from the pipe following the termination of the child process.


