#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/* String examination */
size_t strlen(const char *s);

/* String comparison */
int strcmp(const char *s1, const char *s2);

/* String manipulation */
char *strcpy(char *dest, const char *src);

/* Memory functions */
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#endif /* STRING_H */