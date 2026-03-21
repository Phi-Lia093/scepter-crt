#include "syscall.h"

// int fd = -1;

int main(void)
{
    int fd = -1;
    const char *msg = "Hello from C!\n";
    
    int len = 0;
    while (msg[len] != '\0') {
        len++;
    }
    
    fd = open("/dev/vga0", O_RDWR);
    write(fd, msg, len);

    if(fork()){
        write(fd, "AAA\n", 4);
    }else{
        write(fd, "BBB\n", 4);
        exit(0);
    }
    
    while(1);
}