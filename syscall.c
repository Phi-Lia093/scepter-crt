/* ============================================================================
 * System Call Wrapper Library
 * Provides C function wrappers for kernel syscalls via int 0x80
 * ============================================================================ */

/* Syscall numbers (must match kernel/syscall.h) */
#define SYS_EXIT   1
#define SYS_FORK   2
#define SYS_READ   3
#define SYS_WRITE  4
#define SYS_OPEN   5
#define SYS_CLOSE  6
#define SYS_WAIT4  7

/* ============================================================================
 * Syscall invocation helper
 * ============================================================================ */

static inline int syscall0(int num)
{
    int ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(num)
        : "memory", "ebx", "ecx", "edx", "esi", "edi", "ebp"
    );
    return ret;
}

static inline int syscall1(int num, int arg1)
{
    int ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(num), "b"(arg1)
        : "memory", "ecx", "edx", "esi", "edi", "ebp"
    );
    return ret;
}

static inline int syscall2(int num, int arg1, int arg2)
{
    int ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(num), "b"(arg1), "c"(arg2)
        : "memory", "edx", "esi", "edi", "ebp"
    );
    return ret;
}

static inline int syscall3(int num, int arg1, int arg2, int arg3)
{
    int ret;
    __asm__ volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3)
        : "memory", "esi", "edi", "ebp"
    );
    return ret;
}

/* ============================================================================
 * System call wrappers
 * ============================================================================ */

void exit(int status)
{
    syscall1(SYS_EXIT, status);
    /* Never returns */
    while(1);
}

int fork(void)
{
    return syscall0(SYS_FORK);
}

int wait(int *status)
{
    return syscall1(SYS_WAIT4, (int)status);
}

int open(const char *path, int flags)
{
    return syscall2(SYS_OPEN, (int)path, flags);
}

int read(int fd, void *buf, unsigned int count)
{
    return syscall3(SYS_READ, fd, (int)buf, (int)count);
}

int write(int fd, const void *buf, unsigned int count)
{
    return syscall3(SYS_WRITE, fd, (int)buf, (int)count);
}

int close(int fd)
{
    return syscall1(SYS_CLOSE, fd);
}