/* ============================================================================
 * System Call Interface Header
 * ============================================================================ */

#ifndef SYSCALL_H
#define SYSCALL_H

/* Standard file descriptors */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* Open flags */
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR   2

/* ============================================================================
 * System call function declarations
 * ============================================================================ */

/**
 * exit - Terminate the calling process
 * @status: Exit status code
 * 
 * This function never returns.
 */
void exit(int status) __attribute__((noreturn));

/**
 * fork - Create a child process
 * 
 * Returns: Child PID in parent, 0 in child, -1 on error
 */
int fork(void);

/**
 * wait - Wait for child process to exit
 * @status: Pointer to store child exit status (can be NULL)
 * 
 * Returns: Child PID on success, -1 on error
 */
int wait(int *status);

/**
 * open - Open a file
 * @path: Path to file
 * @flags: Open flags (O_RDONLY, O_WRONLY, O_RDWR)
 * 
 * Returns: File descriptor on success, -1 on error
 */
int open(const char *path, int flags);

/**
 * read - Read from file descriptor
 * @fd: File descriptor
 * @buf: Buffer to read into
 * @count: Number of bytes to read
 * 
 * Returns: Bytes read on success, -1 on error
 */
int read(int fd, void *buf, unsigned int count);

/**
 * write - Write to file descriptor
 * @fd: File descriptor
 * @buf: Buffer to write from
 * @count: Number of bytes to write
 * 
 * Returns: Bytes written on success, -1 on error
 */
int write(int fd, const void *buf, unsigned int count);

/**
 * close - Close file descriptor
 * @fd: File descriptor
 * 
 * Returns: 0 on success, -1 on error
 */
int close(int fd);

#endif /* SYSCALL_H */