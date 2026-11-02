#ifndef _TEST_CONSOLE_H
#define _TEST_CONSOLE_H 1

#include <system/system.h>

inline int putchar(int c)
{
    tty_putc(c);
    return c;
}

inline int puts(const char *s)
{
    tty_puts(s);
    return 0;
}

#endif /* _TEST_CONSOLE_H */
