#include "syscall.h"

int main(void)
{
    open("/dev/kbd0", O_RDWR);
    open("/dev/vga0", O_RDWR);
    open("/dev/vga0", O_RDWR);
    
    write(1, "running init program\n", 21);

    if(fork()){
        
    }else{
        exec("/sh");
        write(1, "exec failed\n", 12);
        exit(-1);
    }
    
    
    while(1);
}