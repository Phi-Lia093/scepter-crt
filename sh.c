#include "syscall.h"

int main(void)
{
    write(1, "This is shell\n", 14);
    exit(0);
}