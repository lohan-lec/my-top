# My Top

## Overview
`my_top` is a system monitoring tool that provides a dynamic real-time view of the processes running on a Unix-like operating system. It displays system summary information as well as a list of tasks currently being managed by the kernel.

## Features
- Display CPU usage
- Display memory usage
- Display process information
- Sort processes by username
- Send signals to processes

## Installation
To build the `my_top` program, you need to have `gcc` and `make` installed on your system. Follow these steps to compile the program:

1. Clone the repository:
    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. Compile the program:
    ```sh
    make
    ```

## Usage
To run the `my_top` program, simply execute the compiled binary:
```sh
./my_top
```

### Command Line Options
- `-U <username>`: Filter processes by username.
- `-d <seconds>`: Set the delay between updates.
- `-n <number>`: Set the maximum number of updates before exiting.

Example:
```sh
./my_top -U root -d 2 -n 10
```

### Interactive Commands
- `q`: Quit the program.
- `KEY_DOWN`: Scroll down the process list.
- `KEY_UP`: Scroll up the process list.
- `k`: Send a signal to a process.

## Functionality
### Display Information
The program displays the following information:
- **CPU Usage**: User, system, nice, idle, iowait, irq, softirq, steal.
- **Memory Usage**: Total, free, used, buffer/cache, swap total, swap free, swap used, available memory.
- **Processes**: PID, user, priority, nice value, virtual memory size, resident set size, shared memory size, state, CPU usage percentage, memory usage percentage, running time, command.

### Process Management
- **Send Signal**: You can send a signal to a process by pressing `k` and entering the PID and signal number.

## Cleaning Up
To remove the compiled binary, run:
```sh
make clean
```

To remove all generated files, run:
```sh
make fclean
```

To recompile the program, run:
```sh
make re
```

## License
This project is licensed under the GNU V3 License.

## Authors
- Lohan Lec

For more information, refer to the source code and comments within the files.
