#ifndef _PICOS_IRQ_H
#define _PICOS_IRQ_H 1

/* Conditional trap codes */
#define CTRAP_SCHEDULE	 0	/* Need scheduling */
#define CTRAP_SEM_YIELD	 1	/* Yield from sem_up() */
#define CTRAP_KILL	30	/* The current thread died */
#define CTRAP_DIE	31	/* The entire system died */

#ifndef __ASSEMBLER__

#include <stddef.h>

typedef void (*irq_handler_t)(unsigned int irq, unsigned int taskno);
extern irq_handler_t trap_table[];

static inline irq_handler_t
set_trap_handler(int n, irq_handler_t handler)
{
    irq_handler_t old_handler = trap_handler[n];
    if (handler)
	trap_handler[n] = handler;
    return old_handler;
}
static inline irq_handler_t
get_trap_handler(int n)
{
    return set_trap_handler(n, NULL);
}

static inline irq_handler_t
set_irq_handler(int n, irq_handler_t handler)
{
    return set_trap_handler(-n, handler);
}
static inline irq_handler_t
get_irq_handler(int n, irq_handler_t handler)
{
    return set_trap_handler(-n, NULL);
}

static inline irq_handler_t
set_ctrap_handler(int n, irq_handler_t handler)
{
    return set_trap_handler(n+32, handler);
}
static inline irq_handler_t
get_ctrap_handler(int n, irq_handler_t handler)
{
    return set_trap_handler(n+32, NULL);
}

#endif

#endif /* _PICOS_IRQ_H */
