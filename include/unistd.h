#ifndef UNISTD_H
#define UNISTD_H

#include <stddef.h>

/* Standard file descriptors */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* Seek whence values */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

/* Process identification */
int getpid(void);
int getppid(void);

/* File operations */
int read(int fd, void *buf, unsigned int count);
int write(int fd, const void *buf, unsigned int count);
int close(int fd);
int lseek(int fd, int offset, int whence);
int dup(int oldfd);
int dup2(int oldfd, int newfd);

/* Directory operations */
char *getcwd(char *buf, unsigned int size);

/* Process control */
int fork(void);
int exec(const char *path);
void exit(int status) __attribute__((noreturn));

#endif /* UNISTD_H */