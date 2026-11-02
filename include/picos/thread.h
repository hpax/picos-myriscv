#ifndef _PICOS_THREAD_H
#define _PICOS_THREAD_H 1

#include <picos/macros.h>
#include <picos/time.h>

struct semaphore;

struct picos_thread {
    uintptr_t pc;
    struct semaphore *blocker;
};

extern unsigned int ___runnable;

extern __thread struct picos_thread *__thread_struct;

typedef unsigned int task_t;

/* Gives the current thread number, even in the kernel */
__always_inline __constfunc task_t this_thread(void)
{
    task_t t;
    asm("csrr %0, myriscv.user_context" : "=r" (t));
    return t;
}

/* Get the thread pointer from the current user task, even in system mode */
__always_inline __purefunc struct picos_thread *current(void)
{
    struct picos_thread *tp;
    asm("add.xu %0, tp, zero" : "=r" (tp));
    return tp;
}

/* Forcibly update the current thread pointer in system mode */
__always_inline void __get_user_tp(void)
{
    asm volatile("add.xu tp, tp, zero" : : : "memory");
}

/* Switch to a specific other thread */
noreturn void ___switch_to(void);

#endif /* _PICOS_THREAD_H */
