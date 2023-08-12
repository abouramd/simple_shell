# Simple UNIX Command Interpreter (Shell) Project

<!-- ![Shell](https://github.com/yourusername/simple-shell/raw/main/images/shell.png) -->

This is a simple UNIX command interpreter, also known as a shell, developed as part of the ALX SE curriculum. The purpose of this project is to gain a deep understanding of various programming concepts, the C programming language, and the fundamentals of UNIX systems. The project is based on the teachings of Julien Barbier and is aimed at improving your skills in:

- Programming basics
- C programming
- Engineering mindset
- Group collaboration
- Learning how to learn

## Table of Contents

- [Background](#background)
- [Learning Objectives](#learning-objectives)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Usage](#usage)

## Background

The foundation of this project is laid out in Julien Barbier's guidance, emphasizing the importance of understanding, learning, and collaboration. It is a group project that challenges participants to apply their knowledge in a practical setting and encourages learning from scratch rather than relying on shortcuts or cheating. The project focuses on developing a functional shell while following the principles of programming ethics, such as avoiding plagiarism and writing code from scratch.

## Learning Objectives

Upon completion of this project, participants are expected to have a clear understanding of the following concepts:

- Origins of Unix and its original designers
- Evolution of the Unix shell and its early versions
- Ken Thompson and his contributions
- Working principles of a shell
- Process IDs (PID) and Parent Process IDs (PPID)
- Environment manipulation for processes
- Differences between functions and system calls
- Process creation and execution
- Utilizing the PATH variable to locate programs
- Executing programs using the `execve` system call
- Process suspension and termination
- Handling "end-of-file" (EOF) in input
- Copyright and plagiarism awareness

## Requirements

- Allowed editors: vi, vim, emacs
- Compiled on Ubuntu 20.04 LTS using `gcc` with options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Files should use the Betty coding style and pass `betty-style.pl` and `betty-doc.pl`
- Memory leaks should be avoided
- Maximum of 5 functions per file
- All header files should have include guards
- Use system calls only when necessary
- Include a `README.md` describing the project and its usage
- An `AUTHORS` file listing contributors
- Collaboration via GitHub repository with proper naming and collaborators

## Getting Started

Follow these steps to get started with the shell project:

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/simple-shell.git
   cd simple-shell
   ```

2. Write your shell implementation in the provided source files.

3. Compile your shell using the provided compilation command:

   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

## Usage

### Interactive Mode

Run your shell in interactive mode by executing the compiled binary:

```bash
./hsh
```

You should see a shell prompt where you can enter commands:

```bash
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

### Non-Interactive Mode

You can also run your shell in non-interactive mode by piping commands into it:

```bash
echo "/bin/ls" | ./hsh
```

### Test Suite

A comprehensive test suite has been provided to help you verify the functionality of your shell. This suite includes regular tests and edge cases for each task. You can run the test suite using the Checker tool, which will be released near the project deadline.

