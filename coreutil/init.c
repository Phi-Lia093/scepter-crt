#include "syscall.h"
#include "stdio.h"

int main(void)
{
    // init stdio env for all processes
    open("/dev/tty0", O_RDWR);
    dup(0);
    dup(0);
    ioctl(STDOUT_FILENO, IOCTL_TTY_CLEAR, 0);
    
    printf("running init program...invoke /sh\n");

    if(fork()){
        
    }else{
        exec("/bin/sh");
        printf("invoke shell failed\n");
        exit(-1);
    }

    while(1);
}