# pipex 🔗
  
This project is about creating a pipeline of processes, replicating the behavior of the Unix shell’s `|` (pipe) operator in C. The aim is to deepen the understanding of process management, file descriptors, and inter-process communication in Unix-based systems.

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Requirements](#project-requirements)
- [Understanding Pipes](#understanding-pipes)
- [Author](#author)

## About the Project

The **pipex** project is part of the [42 School](https://42.fr/) curriculum, aiming to replicate the functionality of shell pipelines. Given two commands, `pipex` redirects the output of the first command into the input of the second command, just like `|` in the shell.

This project is an exercise in:
- Understanding and working with Unix system calls.
- Managing file descriptors and creating pipes between processes.
- Gaining familiarity with process management functions like `fork`, `execve`, `dup2`, and `waitpid`.

## Features

- Creates a pipeline between two commands, executing them sequentially.
- Supports redirection of input and output files.
- Mimics the functionality of `cmd1 | cmd2 > outfile` in shell.
- Error handling for invalid commands, files, and other potential issues.

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/asut00/pipex.git
   cd pipex
   ```

2. **Compile the program**:
   ```bash
   make
   ```
   This generates an executable `pipex` that can be used for piping commands.

## Usage

To use **pipex**, run the executable with the following arguments:

```bash
./pipex infile "command1" "command2" outfile
```

This command is equivalent to running the following in a shell:

```bash
< infile command1 | command2 > outfile
```

### Example

```bash
./pipex input.txt "grep '42'" "wc -l" output.txt
```

In this example:
- The program reads from `input.txt`, runs `grep '42'` on it, then pipes the output to `wc -l`, and writes the final result to `output.txt`.

## Project Requirements

- **Error Management**: Proper handling of invalid commands, missing files, or permissions issues is essential.
- **Pipe and Process Management**: The program must use `pipe` to create communication channels and `fork` to handle multiple processes.
- **File Descriptors**: Use `dup2` to redirect input and output between files and commands.
- **No Memory Leaks**: Ensure that all memory allocated dynamically is freed and that file descriptors are properly closed.

## Understanding Pipes

Pipes in Unix are used for inter-process communication, allowing the output of one process to be the input of another. In **pipex**, the `pipe` system call is used to create a communication channel between two commands.

### Key Functions Used
- **pipe**: Creates a unidirectional data channel that can be used for communication.
- **fork**: Creates a new process, allowing concurrent execution.
- **execve**: Replaces the current process with a new process.
- **dup2**: Redirects file descriptors to control input and output.
- **waitpid**: Waits for a child process to finish, ensuring the parent process knows when to proceed.

## Author

- GitHub: [@asut00](https://github.com/asut00)  
- 42 Intra: `asuteau`
