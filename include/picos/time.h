#ifndef _PICOS_TIME_H
#define _PICOS_TIME_H 1

#include <picos/macros.h>

typedef uint32_t ticks_t;

static inline ticks_t ticks_now(void)
{
    ticks_t __now;
    asm("csrr %0,cycle" : "=r" (__now));
    return __now;
}

#endif /* _PICOS_TIME_H */
