/* Simple printf implementation */
extern int putchar(int c);
extern unsigned long strlen(const char *s);

/* Helper: print string */
static void print_str(const char *s)
{
    while (*s)
        putchar(*s++);
}

/* Helper: print unsigned int in given base */
static void print_uint(unsigned int n, int base)
{
    char buf[32];
    int i = 0;
    const char *digits = "0123456789abcdef";
    
    if (n == 0) {
        putchar('0');
        return;
    }
    
    while (n > 0) {
        buf[i++] = digits[n % base];
        n /= base;
    }
    
    while (i > 0)
        putchar(buf[--i]);
}

/* Helper: print signed int */
static void print_int(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    print_uint((unsigned int)n, 10);
}

int printf(const char *fmt, ...)
{
    unsigned int *args = (unsigned int *)(&fmt + 1);
    int arg_idx = 0;
    
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    const char *s = (const char *)args[arg_idx++];
                    if (s)
                        print_str(s);
                    else
                        print_str("(null)");
                    break;
                }
                case 'd':
                case 'i':
                    print_int((int)args[arg_idx++]);
                    break;
                case 'u':
                    print_uint(args[arg_idx++], 10);
                    break;
                case 'x':
                    print_uint(args[arg_idx++], 16);
                    break;
                case 'c':
                    putchar((char)args[arg_idx++]);
                    break;
                case '%':
                    putchar('%');
                    break;
                default:
                    putchar('%');
                    putchar(*fmt);
                    break;
            }
            fmt++;
        } else {
            putchar(*fmt++);
        }
    }
    
    return 0;
}