/* Declare strlen and putchar */
extern unsigned long strlen(const char *s);
extern int putchar(int c);

int puts(const char *s)
{
    while (*s)
        putchar(*s++);
    putchar('\n');
    return 0;
}