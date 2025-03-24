# 2.24 Problem Statement

In Section 2.3, we described a program that copies the contents of one file to a destination file. This program works by first prompting the user for the name of the source and destination files.

## Task

Write this program using either the Windows or POSIX API.

## Requirements

Include all necessary error checking, including ensuring that the source file exists. Once the program is correctly designed and tested, run it using a utility that traces system calls (if supported by your system).

## System-Specific Instructions

- *Linux systems*: Use the `strace` utility.

- *Solaris & Mac OS X systems*: Use the `dtrace` command.

- *Windows systems*: Since Windows does not provide such features, you will need to trace through the Windows version of this program using a debugger.