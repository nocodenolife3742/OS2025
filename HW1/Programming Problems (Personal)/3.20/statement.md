# 3.20 Problem Statement

An operating system’s pid manager is responsible for managing process identifiers.
When a process is first created, it is assigned a unique pid by the pid manager.  
The pid is returned to the pid manager when the process completes execution, and the manager may later reassign this pid.  

Process identifiers are discussed more fully in Section 3.3.1.  
What is most important here is to recognize that process identifiers must be unique; no two active processes can have the same pid.

## Constants for PID Range

```c
#define MIN_PID 300
#define MAX_PID 5000
```

You may use any data structure of your choice to represent the availability of process identifiers.  
One strategy is to adopt what Linux has done and use a bitmap in which:  
- A value of `0` at position `i` indicates that a process id of value `i` is available.  
- A value of `1` indicates that the process id is currently in use.

## API Implementation

Implement the following API for obtaining and releasing a pid:

```c
int allocate_map(void);
// Creates and initializes a data structure for representing pids.
// Returns −1 if unsuccessful, 1 if successful.

int allocate_pid(void);
// Allocates and returns a pid.
// Returns −1 if unable to allocate a pid (all pids are in use).

void release_pid(int pid);
// Releases a pid.
```
