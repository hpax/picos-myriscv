#ifndef _MYRISCV_LRSC_H
#define _MYRISCV_LRSC_H 1

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

static inline int _lr_b(const volatile int8_t *p)
{
    int v;
    asm volatile("lr.b %[v],%[addr]"
		 : [v] "=r" (v)
		 : [addr] "A" (*p)
		 : "memory");
    return v;
}
static inline int _sc_b(volatile int8_t *p, int8_t v)
{
    int err;
    asm volatile("sc.b %[err], %[v],%[addr]"
		 : [err] "=r" (err), [addr] "+A" (*p)
		 : [v] "r" (v)
		 : "memory");
    return err;
}

static inline int _lr_h(const volatile int16_t *p)
{
    int v;
    asm volatile("lr.h %[v],%[addr]"
		 : [v] "=r" (v)
		 : [addr] "A" (*p)
		 : "memory");
    return v;
}
static inline int _sc_h(volatile int16_t *p, int16_t v)
{
    int err;
    asm volatile("sc.h %[err], %[v],%[addr]"
		 : [err] "=r" (err), [addr] "+A" (*p)
		 : [v] "r" (v)
		 : "memory");
    return err;
}

static inline int _lr_w(const volatile int32_t *p)
{
    int v;
    asm volatile("lr.w %[v],%[addr]"
		 : [v] "=r" (v)
		 : [addr] "A" (*p)
		 : "memory");
    return v;
}
static inline int _sc_w(volatile int32_t *p, int32_t v)
{
    int err;
    asm volatile("sc.w %[err], %[v],%[addr]"
		 : [err] "=r" (err), [addr] "+A" (*p)
		 : [v] "r" (v)
		 : "memory");
    return err;
}

#endif
