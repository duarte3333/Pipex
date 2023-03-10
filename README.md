# Pipex

## What multiprogramming?

The basic idea behind multiprogramming is that while one program is waiting for I/O (e.g., reading data from a file), the CPU can switch to another program that is ready to run. This way, the CPU is kept busy running programs, even when some programs are waiting for external events to occur. 

Multiprogramming can lead to increased efficiency and utilization of system resources.

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled.png)

## What is a process ?

A process is a running instance of a program. It consists of one or more threads of execution, as well as associated memory, file descriptors, and other system resources. Processes are managed by the operating system and can run concurrently with other processes on the same system. Each process is assigned a unique PID by the operating system, which can be used to identify and manipulate the process.

Processes are a fundamental concept in modern operating systems and are used to provide a mechanism for running multiple programs or tasks concurrently. They can also be used to implement multiprocessing and multitasking, where multiple processes can run simultaneously on different cores or CPUs, or on the same CPU using time-sharing techniques.

## What is the function fork() ?

In C programming, the **`fork()`** function is used to create a new process by duplicating the calling process. The new process is referred to as the child process, while the original process is referred to as the parent process.

When **`fork()`** is called, a new process is created that is a copy of the calling process. Both processes then continue executing from the point where the **`fork()`** function was called. The new process gets its own unique process ID (PID), while the parent process retains its original PID.

The child process and parent process run independently of each other and have their own memory space, CPU registers, and file descriptors. The child process can modify its own memory space, but any changes made by the child process do not affect the parent process.

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled%201.png)

[data:image/svg+xml,%3csvg%20xmlns=%27http://www.w3.org/2000/svg%27%20version=%271.1%27%20width=%2730%27%20height=%2730%27/%3e](data:image/svg+xml,%3csvg%20xmlns=%27http://www.w3.org/2000/svg%27%20version=%271.1%27%20width=%2730%27%20height=%2730%27/%3e)

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled%202.png)

## What is a pipe?

**Definition:** A pipe is a method for interprocess communication (IPC) that allows one process to send data to another process. A pipe consists of two ends, a read end and a write end. The write end is used to send data to the pipe, and the read end is used to receive data from the pipe.

**Simple Definition:** A pipe is like a tube that connects two processes or programs. One end of the pipe is used to send data and the other end is used to receive it.

For example, if two friends are sitting in different rooms and they want to pass notes to each other. They can use a tube (or pipe) to send the notes back and forth.

**Example:** Sending a message of Hello World from a child process to a parent process

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2]; // file descriptor array for the pipe
    pid_t pid; // process ID
    char message[] = "Hello, World!"; // the message to send through the pipe

    if (pipe(fd) < 0) { // create the pipe
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    pid = fork(); // fork a child process
    if (pid == 0) { // child process
        close(fd[0]); // close the read end of the pipe
        write(fd[1], message, sizeof(message)); // send the message through the pipe
        close(fd[1]); // close the write end of the pipe
    } else { // parent process
        close(fd[1]); // close the write end of the pipe
        char buffer[sizeof(message)]; // create a buffer to store the received message
        read(fd[0], buffer, sizeof(buffer)); // receive the message from the pipe
        printf("Received message: %s\n", buffer); // print the received message
        close(fd[0]); // close the read end of the pipe
    }
    return 0;
```

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled%203.png)

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled%204.png)

## What is the function pipe()?

In C, the **`pipe()`** function is used to create an interprocess communication channel (IPC) between a parent process and a child process. The channel is typically used to send data from the parent process to the child process or vice versa.

The **`pipe()`** function creates a pair of file descriptors, one for the read end of the pipe and one for the write end of the pipe. The file descriptors are returned in an array, where the first element is the read end of the pipe and the second element is the write end of the pipe. The parent process can then use the write end of the pipe to send data to the child process, and the child process can use the read end of the pipe to receive the data.

## What the function exit()?

In programming, the **`exit()`** function is used to terminate the current process and return a status code to the calling process. When a program calls **`exit()`**, it immediately stops execution and exits the program.

## What is the function wait()?

In computing, the **`wait()`** function is a system call that is used in Unix-based operating systems to suspend the execution of a process until one of its child processes terminates.

The **`wait()`** function takes a pointer to an integer variable, which will be used to store the exit status of the child process. If the child process terminated abnormally or was terminated by a signal, the exit status will be a negative integer.

## What is a shell?

A shell is a program that provides a user interface for accessing an operating system's services and resources. It is typically a command-line interface that allows users to interact with the operating system by typing commands, rather than using a graphical user interface.

There are several popular shells available in Unix-like operating systems, including:

- **`bash`**: The Bourne-Again SHell, which is the default shell in most Linux distributions.
- **`zsh`**: The Z SHell, which is an enhanced version of **`bash`** with additional features and customization options.
- **`fish`**: The Friendly Interactive SHell, which is designed to be more user-friendly and intuitive than other shells.
- **`ksh`**: The Korn SHell, which is an alternative to the **`bash`** shell and provides some additional features and improvements.

Each shell has its own syntax and features, but they all provide a similar basic interface for interacting with the operating system.

**Example of a small shell:**

```c
while (TRUE) {
  prompt();
  read_command(command, params);
  pid = fork();
  if (pid < 0) {
    printf ("Unable to fork"); // Erro no fork
    continue;
  }
  if (pid != 0) {
    wait(&status); // Se o fork gerar um pai
  } else{
    execv(command, params);
  }
}
```

## How to execute commands in UNIX?

The **`execve()`** function is a system call in C that is used to execute a program. It replaces the current process image with a new process image specified by the file path and arguments passed as parameters. This system call is one of several **`exec()`**-related functions available in C, each with slightly different behavior:

- **`execl()`**, **`execv()`**: These functions are similar to **`execve()`**, but instead of passing an array of arguments, they take a variable number of arguments. The first argument is the file path of the program to execute, and subsequent arguments are the command-line arguments passed to the program.
- **`execle()`**, **`execve()`**: These functions are like **`execl()`** and **`execv()`**, but they also allow you to specify the environment for the new process as an array of strings.
- **`execlp()`**, **`execvp()`**: These functions are similar to **`execl()`** and **`execv()`**, but they search the **`PATH`** environment variable to locate the program file if it is not found in the current directory.

**Note:**  these functions do not create a new process; instead, they replace the current process image with a new one.

## What is a thread?

In computing, a thread is the smallest unit of execution that can be scheduled by the operating system. A thread is a sequence of instructions that can be executed independently by a computer's CPU, and it typically represents a single task or a part of a larger program. Multiple threads can exist within the same process, and each thread has its own stack, registers, and program counter.

Threads are often used to improve the performance and responsiveness of programs, as they can allow multiple tasks to be executed concurrently. For example, a web server might use threads to handle multiple requests from different clients at the same time.

Threads can also be used to implement parallelism in a program, where multiple threads work together to complete a task more quickly. Parallelism is often used in scientific computing, video rendering, and other computationally intensive tasks.

## What is the difference between a process and a thread?

The main difference between a thread and a process is that a process is a running instance of a program, while a thread is a sub-component of a process that can be scheduled for execution by the operating system.

A process consists of one or more threads of execution, as well as associated memory, file descriptors, and other system resources. Each process is managed by the operating system and has its own unique process ID (PID), which can be used to identify and manipulate the process.

On the other hand, a thread is a lightweight process that exists within a process. Multiple threads can exist within the same process, and each thread has its own stack, registers, and program counter. Threads within a process share the same memory space, file descriptors, and other system resources, allowing them to communicate and share data more efficiently than if they were separate processes.

The main advantage of using threads over processes is that threads are lighter weight and can be created and destroyed more quickly than processes. This makes them ideal for implementing concurrency within a program, as multiple threads can work together to complete a task more quickly. However, threads also pose some challenges, such as the potential for race conditions and deadlocks, which must be carefully managed by the programmer.

## How to know the PID and other informations?

In Unix-based operating systems, the **`getpid()`** function is a system call that is used to retrieve the process ID (PID) of the current process. The PID is a unique identifier that is assigned to each process by the operating system when it is created.

The **`getpid()`** function is part of a group of related functions that allow processes to interact with the operating system and manage their own execution. These functions include:

- **`getpid()`**: retrieves the process ID of the current process.
- **`getppid()`**: retrieves the process ID of the parent process.
- **`getuid()`**: retrieves the user ID (UID) of the current process.
- **`getgid()`**: retrieves the group ID (GID) of the current process.
- **`geteuid()`**: retrieves the effective user ID of the current process.
- **`getegid()`**: retrieves the effective group ID of the current process.

## What is a FIFO?

In C, a FIFO (First-In-First-Out) is a type of named pipe that allows interprocess communication (IPC) between processes. It is called "first-in-first-out" because the first data that is written into the pipe is also the first data that is read from it.

A FIFO is implemented as a special type of file in the file system. It can be created using the **`mkfifo()`** function, which takes a file path as an argument and creates a new FIFO with that name. Once a FIFO is created, it can be opened and used like any other file in the file system.

The **`open()`** function is used to open a FIFO for reading or writing. When a process opens a FIFO for reading, it blocks until another process opens the same FIFO for writing. Similarly, when a process opens a FIFO for writing, it blocks until another process opens the same FIFO for reading. Once both processes have opened the FIFO, data can be transferred between them using the **`read()`** and **`write()`** functions.

FIFOs are commonly used in Unix-based systems for IPC between processes. They can be used to send large amounts of data between processes, and they can also be used to synchronize access to shared resources. Unlike unnamed pipes (created using the **`pipe()`** function), FIFOs can be accessed by multiple processes at the same time, making them a useful tool for interprocess communication in many different scenarios.

## Difference between named pipes and unnamed pipes?

Both unnamed pipes and named pipes (FIFOs) are used for interprocess communication (IPC) between processes, but there are some key differences between them.

1. Naming: Unnamed pipes have no name, while named pipes have a name that is associated with them in the file system. This means that named pipes can be accessed by multiple processes using their name, while unnamed pipes can only be accessed by the two processes that created them.
2. Persistence: Named pipes are persistent, which means they remain in the file system even after the processes that created them have exited. Unnamed pipes, on the other hand, are destroyed when the processes that created them exit.
3. Synchronization: Named pipes can be used to synchronize access to shared resources, as multiple processes can open the same named pipe and wait for data to be written to it. Unnamed pipes, however, can only be accessed by the two processes that created them, so they cannot be used for synchronization between multiple processes.
4. Accessibility: Named pipes can be accessed by any process with the appropriate permissions, as they are created in the file system and have a unique name. Unnamed pipes, on the other hand, are only accessible by the two processes that created them and cannot be accessed by other processes.

## Two way communication using pipes

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd1[2], fd2[2]; // file descriptor arrays to store the read and write ends of the pipes
    pid_t pid; // process ID variable

    // create the first pipe
    if (pipe(fd1) == -1) {
        perror("pipe");
        return 1;
    }
    // create the second pipe
    if (pipe(fd2) == -1) {
        perror("pipe");
        return 1;
    }
    // create a child process
    if ((pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // child process
        close(fd1[1]); // close the write end of the first pipe
        close(fd2[0]); // close the read end of the second pipe

        char buffer[100]; // buffer to store incoming data
        read(fd1[0], buffer, sizeof(buffer)); // read data from the first pipe
        printf("Child received: %s\n", buffer);

        char *msg = "Hello, parent!"; // message to send to parent process
        write(fd2[1], msg, sizeof(msg)); // write data to the second pipe

        close(fd1[0]); // close the read end of the first pipe
        close(fd2[1]); // close the write end of the second pipe
    } else { // parent process
        close(fd1[0]); // close the read end of the first pipe
        close(fd2[1]); // close the write end of the second pipe

        char *msg = "Hello, child!"; // message to send to child process
        write(fd1[1], msg, sizeof(msg)); // write data to the first pipe

        char buffer[100]; // buffer to store incoming data
        read(fd2[0], buffer, sizeof(buffer)); // read data from the second pipe
        printf("Parent received: %s\n", buffer);

        close(fd1[1]); // close the write end of the first pipe
        close(fd2[0]); // close the read end of the second pipe
    }

    return 0;
}
```

For two-way communication, you need to use two file descriptors to establish two pipes - one for communication from the parent process to the child process, and another for communication from the child process to the parent process.

![Untitled](Pipex%2006c13c870d2e41a0886a0be544d46be9/Untitled%205.png)

## How to change permissions of a file in Linux?

In Linux, you can change the file permissions of a file using the **`chmod`** command in the terminal. The **`chmod`** command changes the permissions of a file according to the specified mode, which can be specified using either symbols or numbers.

Here are some examples of how to use the **`chmod`** command to change file permissions:

1. Using symbols:
    
    ```bash
    bashCopy code
    chmod u+rwx myfile.txt   # Add read, write, and execute permissions for the owner
    chmod g-rw myfile.txt   # Remove read and write permissions for the group
    chmod o=r myfile.txt   # Set read-only permissions for others
    chmod a+x myfile.txt   # Add execute permissions for all users
    ```
    
    In this example, the **`u`**, **`g`**, and **`o`** symbols refer to the owner, group, and others, respectively. The **`+`** and **`-`** symbols are used to add or remove permissions, while the **`=`** symbol is used to set permissions to a specific value. The **`r`**, **`w`**, and **`x`** symbols refer to read, write, and execute permissions, respectively.
    
2. Using numbers:
    
    ```bash
    bashCopy code
    chmod 755 myfile.txt   # Set read, write, and execute permissions for the owner, and read and execute permissions for group and others
    chmod 644 myfile.txt   # Set read and write permissions for the owner, and read-only permissions for group and others
    chmod 777 myfile.txt   # Set read, write, and execute permissions for all users
    ```
    
    In this example, the numbers represent the file permissions in octal notation. The first digit represents the owner's permissions, the second digit represents the group's permissions, and the third digit represents the permissions for others. The values of the digits are calculated by adding up the values of the permissions: 4 for read, 2 for write, and 1 for execute. For example, **`755`** corresponds to **`rwxr-xr-x`** (owner has all permissions, group and others have read and execute permissions only).
    

Note that in order to change file permissions, you must have permission to modify the file. If the file is owned by another user or if you don't have permission to modify it, you will need to use **`sudo`** or ask the owner of the file to change the permissions.