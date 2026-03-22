int atoi(const char *s)
{
    int result = 0;
    int sign = 1;
    
    /* Skip whitespace */
    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;
    
    /* Handle sign */
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }
    
    /* Convert digits */
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    
    return sign * result;
}