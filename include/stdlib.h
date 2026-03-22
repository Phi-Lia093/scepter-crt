#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

/* Memory allocation */
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

/* String conversion */
int atoi(const char *s);

/* Absolute value */
int abs(int n);
long labs(long n);

/* Process control - from syscall.h */
void exit(int status) __attribute__((noreturn));

#endif /* STDLIB_H */
