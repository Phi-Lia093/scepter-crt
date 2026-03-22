/* Declare write syscall */
extern int write(int fd, const void *buf, unsigned int count);

int putchar(int c)
{
    char ch = (char)c;
    write(1, &ch, 1);
    return (unsigned char)c;
}