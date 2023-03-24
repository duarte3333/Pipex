# Pipex

## What is the goal of the project?

The goal of the pipex project is to create a program that can mimic the behavior of the shell command **`"< file1 cmd1 | cmd2 > file2"`**, where **`cmd1`** reads input from **`file1`**, processes it, and sends the output to **`cmd2`**, which then writes the output to **`file2`**.

The **`pipex`** program takes four arguments: **`file1`**, **`cmd1`**, **`cmd2`**, and **`file2`**. It reads input from **`file1`**, sends it through the pipe to **`cmd2`**, and writes the output to **`file2`**.

The **`pipex`** program must use **`fork()`**, **`dup2()`**, and **`execve()`** to create a child process, redirect its standard input and output to the pipe, and execute the two given commands. It should also handle errors and edge cases, such as invalid arguments, non-existent files, and failed system calls.

##### Simpler explanation

The pipex project is a programming exercise that involves manipulating data in a special way called "piping". Piping is a technique that lets you take the output from one program and use it as the input to another program.

##### Applications

The pipex project has practical applications in many fields, such as data science, networking, and security. For example, in data science, pipelining is a common technique used to process and transform data. In networking, pipelining can be used to create efficient communication channels between client and server applications. In security, pipelining can be used to create custom filters that monitor and analyze network traffic.
In brief: database servers, WWW browser and server, SSH client and server, email client and server, us BitTorrent.

## What is multiprogramming?
<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227653720-09ae8a55-1238-4f9a-844b-41b1f0d8c84c.png" width="500" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

The basic idea behind multiprogramming is that while one program is waiting for I/O (e.g., reading data from a file), the CPU can switch to another program that is ready to run. This way, the CPU is kept busy running programs, even when some programs are waiting for external events to occur. 

Multiprogramming can lead to increased efficiency and utilization of system resources.

## What is a process ?

<u>A process is a running instance of a program.</u> It consists of one or more threads of execution, as well as associated memory, file descriptors, and other system resources. Processes are managed by the operating system and can run concurrently with other processes on the same system. Each process is assigned a unique PID by the operating system, which can be used to identify and manipulate the process.

A process typically includes several components, including:

1. <ins>An executable program</ins>: This is the actual program that you want to run. It contains the instructions that the computer needs to execute in order to perform a particular task.
2. <ins>Memory space</ins>: Each process has its own memory space, which includes the code, data, and stack segments. The code segment contains the executable code for the program, while the data segment contains global and static variables. The stack segment contains the program's stack, which is used to store local variables and function call frames.
3. <ins>System resources</ins>: A process also has access to various system resources, such as file handles, network connections, and other devices.
4. <ins>Process state</ins>: Each process has a state that determines what it is currently doing. Some possible states include "running", "sleeping", "blocked", or "terminated".
5. <ins>Process identifier (PID)</ins>: A PID is a unique identifier assigned to each process by the operating system. PIDs are used to manage and monitor processes on the system.

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227656494-38157229-396f-4f19-8fc2-2cdd6cc564cf.png" width="600"</td>
     </tr>
</div>

Processes are a fundamental concept in modern operating systems and are used to provide a mechanism for running multiple programs or tasks concurrently. They can also be used to implement multiprocessing and multitasking, where multiple processes can run simultaneously on different cores or CPUs, or on the same CPU using time-sharing techniques.

## What is the function fork() ?

In C programming, the **`fork()`** function is used to create a new process by duplicating the calling process. The new process is referred to as the child process, while the original process is referred to as the parent process.

When **`fork()`** is called, a new process is created that is a copy of the calling process. Both processes then continue executing from the point where the **`fork()`** function was called. The new process gets its own unique process ID (PID), while the parent process retains its original PID.
<div align="center">
    <table >
     <!-- <tr>
        <td><b>Latest Tweets</b></td>
        <td><b>daily.dev</b></td>
     </tr> -->
     <tr>
       <td><img src="https://user-images.githubusercontent.com/76222459/227656655-9899db40-ae44-4b32-ad7d-51363da4028b.png" alt="sunil sapkota twitter" > </img></td>
        <td><img src="https://user-images.githubusercontent.com/76222459/227656661-5774de6c-4ecd-47ab-8afc-fad557ac75ad.png" width="300" alt="sunil sapkota's Dev Card"/></td>
     </tr>
    </table>
    </div>

The child process and parent process run independently of each other and have their own memory space, CPU registers, and file descriptors. The child process can modify its own memory space, but any changes made by the child process do not affect the parent process.

## What is a pipe?

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227657406-bbaa54c1-31c8-48b8-b772-3c4bab9d5b94.png" width="400" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

**Definition:** A pipe is a method for </ins>interprocess communication (IPC)</ins> that allows one process to send data to another process. A pipe consists of two ends, a read end and a write end. The write end is used to send data to the pipe, and the read end is used to receive data from the pipe.

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

## What is the function pipe()?

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227661140-fc0360ee-b980-40e7-93f4-f5b7e89b54af.png"/></td>
     </tr>
</div>

In C, the **`pipe()`** function is used to create an interprocess communication channel (IPC) between a parent process and a child process. The channel is typically used to send data from the parent process to the child process or vice versa.

The **`pipe()`** function creates a pair of file descriptors, one for the read end of the pipe and one for the write end of the pipe. The file descriptors are returned in an array, where the first element is the read end of the pipe and the second element is the write end of the pipe. The parent process can then use the write end of the pipe to send data to the child process, and the child process can use the read end of the pipe to receive the data.

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227657438-e939c1eb-95ba-4a6c-80b6-a5775a2a85e3.png" width="500" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

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

## What is the command dup and dup2() ?

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227659378-66ba60fc-af85-49d1-b5ea-2e1e7a23fc79.png" width="500" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

In C, **`dup`** and **`dup2`** are system calls that are used to duplicate a file descriptor. These system calls are defined in the **`<unistd.h>`** header file.

The syntax for **`dup`** in C is:

```c
#include <unistd.h>
int dup(int oldfd);
```



The **`dup`** function takes an integer argument **`oldfd`**, which is the file descriptor that you want to duplicate. It returns a new file descriptor that is a copy of **`oldfd`**, or -1 if an error occurs.

For example, if you have an existing file descriptor **`fd1`** that is associated with a file named "input.txt", and you want to create a new file descriptor **`fd2`** that points to the same file, you can use the following code:

```c
#include <unistd.h>#include <fcntl.h>
...
int fd1 = open("input.txt", O_RDONLY);
int fd2 = dup(fd1);
```

Now you can use both **`fd1`** and **`fd2`** to read from or write to the same file.

The syntax for **`dup2`** in C is:

```c
#include <unistd.h>
int dup2(int oldfd, int newfd);
```

The **`dup2`** function takes two integer arguments **`oldfd`** and **`newfd`**. **`oldfd`** is the file descriptor that you want to duplicate, and **`newfd`** is the number of the new file descriptor that you want to create. If **`newfd`** is already a valid file descriptor, it will be closed first.

For example, if you have an existing file descriptor **`fd1`** that is associated with a file named "input.txt", and you want to create a new file descriptor **`fd2`** that points to the same file, and you want the new file descriptor to have the number 10, you can use the following code:

```c
#include <unistd.h>#include <fcntl.h>
...
int fd1 = open("input.txt", O_RDONLY);
int fd2 = dup2(fd1, 10);
```

Now you can use both **`fd1`** and **`fd2`** to read from or write to the same file, and you can refer to the new file descriptor as **`10`**.
#### Difference between dup() and dup2()

The main difference between dup and dup2 is that dup duplicates the file descriptor passed as argument and returns the lowest unused file descriptor, while dup2 duplicates the file descriptor passed as the first argument onto the file descriptor passed as the second argument.

## What is a pipeline ?

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227659390-c2c35956-627b-41d2-818b-5d0405d31105.png" width="250" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

In computing, a pipeline refers to a series of processes or commands arranged in a sequence where the output of one process is the input of the next process. It allows for the efficient processing of large amounts of data by breaking down complex tasks into smaller, more manageable parts.

Pipelines are often used in Unix/Linux systems, where they are implemented using the pipe character **`|`**. For example, the following command:

```bash
ls | grep .txt | sort
```

will list all files in the current directory, filter out only the ones with a **`.txt`** extension, and sort them alphabetically. The output of the **`ls`** command is piped to the **`grep`** command, which in turn pipes its output to the **`sort`** command. This allows the entire pipeline to be executed as a single command, with each step processing the output of the previous step.

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227659360-8e0ab5c1-c295-4a6e-8950-daedc1f9252b.png" width="500" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>


## What is a thread?

A thread is a separate path of execution within a program. Think of a program as a set of instructions that need to be carried out in order to accomplish a task. A thread is like a subset of those instructions that can be executed independently from the rest of the program.

So, imagine you're cooking dinner and you have several tasks to do, such as chopping vegetables, boiling pasta, and cooking sauce. You could do each of these tasks one after the other, but that would take a long time. Alternatively, you could have multiple threads (i.e. subsets of instructions) running at the same time, with one thread chopping vegetables, another thread boiling pasta, and so on. This would allow you to complete the dinner more quickly and efficiently.

Threads are often used to improve the performance and responsiveness of programs, as they can allow multiple tasks to be executed concurrently. For example, a web server might use threads to handle multiple requests from different clients at the same time.

<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227659830-34878f7f-b639-434c-b8fc-91ffa3810a43.png" width="500" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

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
<div align="center">
        <td> <img src="https://user-images.githubusercontent.com/76222459/227659857-10bd1d96-0f02-4ba9-a0cc-af2dc0b20c53.png" width="450" alt="sunil sapkota's Dev Card"/></td>
     </tr>
</div>

For two-way communication, you need to use two file descriptors to establish two pipes - one for communication from the parent process to the child process, and another for communication from the child process to the parent process.


## What is a here doc in linux ?

To do on bash: cmd << LIMITER | cmd1 >> file

In simpler terms, a "here document" (or "here doc") is a way to pass a block of text to a command or program without having to store the text in a separate file. It's commonly used in Linux or Unix environments.

```bash
cmd <<LIMITER | cmd1 >> file
[Block of text]
LIMITER
```

In this syntax, **`cmd`** is the command or program that will receive the block of text as input, **`LIMITER`** is a special marker that indicates the beginning and end of the block of text, and **`cmd1`** is another command that will receive the output from the first command as input.

The block of text can include any characters, including newlines and other special characters, without needing to escape them. When the shell sees the **`<<LIMITER`** syntax, it knows to collect all subsequent lines of input (up to the line that contains only the **`LIMITER`** marker) and pass them as input to the **`cmd`** command.

After **`cmd`** has processed the input, its output is passed to **`cmd1`**. Finally, the **`>>`** operator is used to append the output to a file.

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

### My notion 
https://polarized-algebra-458.notion.site/Pipex-06c13c870d2e41a0886a0be544d46be9
