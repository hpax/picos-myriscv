#ifndef MYRISCV_SEMAPHORE_H
#define MYRISCV_SEMAPHORE_H 1

/* MyRISCV semaphore interface (tiniest semaphore ever?) */

#include <picos/macros.h>
#include <picos/thread.h>

#include <myriscv/lrsc.h>

struct semaphore {
    /*
     * count serves double duty:
     * if count <= 0 it is - the number of free slots for the semaphore
     * if count >= 0 it is a bitmask of waiters
     * Note that 0 has both meanings!
     */
    int32_t count;
};

/* Blocking down semaphore: NOT safe from machine context */
/* Returns true if the semaphore was acquired */
inline __hot bool sem_try_down(struct semaphore *sem)
{
    bool ok;
    /* Critical region short enough to have guaranteed progress */
    int32_t count = _lr_w(&sem->count);
    ok = __likely(count < 0);
    count += ok;
    _sc_w(&sem->count, count);
    return ok;
}

/* Returns the amount of time slept, if any */
__always_inline ticks_t __sem_down_slow(struct semaphore *sem)
{
    register ticks_t ticks asm("a0") = (uintptr_t)sem;

    asm volatile("call t0, __sem_down_slow_asm"
		 : "=r" (ticks)
		 : "0" (sem)
		 : "t0", "t4", "t5", "t6", "memory");
    return ticks;
}
inline __hot ticks_t sem_down(struct semaphore *sem)
{
    /* Critical region short enough to have guaranteed progress */
    int32_t count = _lr_w(&sem->count);
    if (__likely(count < 0)) {
	_sc_w(&sem->count, count + 1);
	return 0;
    }

    return __sem_down_slow(sem);
}

/* Returns the amount of time slept, if any */
__always_inline ticks_t __sem_up_slow(struct semaphore *sem, int32_t count)
{
    register ticks_t ticks asm("a0");
    register int32_t _cnt  asm("t1") = count;

    asm volatile("call t0, __sem_up_slow_asm"
		 : "=r" (ticks), "+r" (_cnt)
		 : "0" (sem)
		 : "t0", "t4", "t5", "t6", "memory");
    return ticks;
}

inline __hot ticks_t sem_up(struct semaphore *sem)
{
    int32_t count = _lr_w(&sem->count);
    if (__likely(count <= 0)) {
	_sc_w(&sem->count, count - 1);
	return 0;
    }

    return __sem_up_slow(sem, count);
}

#endif /* MYRISCV_SEMAPHORE_H */
