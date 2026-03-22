#include "stdio.h"
#include "stdlib.h"
#include "syscall.h"

int main(void)
{
    printf("Shell started! Testing printf...\n");
    printf("Number: %d\n", 42);
    printf("Hex: 0x%x\n", 255);
    printf("String: %s\n", "Hello from libc!");
    if(!fork()){
        printf("pid=3\n");
        exit(0);
    }
    /* Wait for child (PID 3) to exit and reap it */
    int status;
    wait(&status);
    printf("Child exited with status: %d\n", status);
    while(1);
    exit(0);
}
