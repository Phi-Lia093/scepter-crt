#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>

/* Character I/O */
int putchar(int c);

/* String I/O */
int puts(const char *s);

/* Formatted output */
int printf(const char *fmt, ...);

#endif /* STDIO_H */