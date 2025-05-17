# Operating Systems Lab

This repository contains solutions and code developed during university Operating Systems lab sessions. The labs covered a range of foundational OS concepts and involved both **Bash scripting** and **C programming**, focusing on essential system-level programming skills.

## Contents

### 🖥️ Bash Problems
A collection of shell scripting tasks designed to strengthen skills in:

- File and directory manipulation
- Conditional execution and loops
- Permissions and user management
- Text processing (using `grep`, `awk`, `sed`, etc.)
- Automation of routine tasks

### ⚙️ C Programming Problems
These problems involve interacting directly with OS-level features in C, including:

#### 📁 File Handling
- Reading from and writing to files using system calls (`open`, `read`, `write`, `close`)
- File descriptor manipulation
- Working with file metadata using `stat` and related functions

#### 🔗 Pipes
- Creating and using unnamed pipes (`pipe()`)
- Parent-child communication through pipes
- Redirecting standard input/output

#### 🧵 Threads
- Creating and managing threads using `pthread` library
- Synchronization with mutexes and condition variables
- Avoiding race conditions

#### 👥 Processes
- Creating processes using `fork()`
- Executing programs with `exec` family
- Process synchronization using `wait`, `waitpid`
- Handling signals


## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/os-lab.git
   cd os-lab```
2. Browse to the relevant directory (e.g., bash/, c/pipes/) to find problem-specific source files.

Compile C files using gcc. For example:
    ```bash
    gcc pipes/example.c -o example
    ./example

    ```

Requirements
GCC (for compiling C programs)

Bash (for running shell scripts)

POSIX-compliant OS (Linux recommended)

License
This repository is for educational purposes. You are free to use and modify the code under the terms of the MIT License unless stated otherwise.

Acknowledgements
Thanks to the university Operating Systems course staff and lab instructors for designing the problems and guiding the sessions.


