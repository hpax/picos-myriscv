#ifndef _TEST_SYSTEM_H
#define _TEST_SYSTEM_H 1

#include <system/riscv.h>
#include <system/params.h>

/*
 * Test output status codes - all constants directly correspond to the
 * four-letter ASCII string in the name (space-padded if necessary)
 */
#define _TEST(a,b,c,d) ((a)+((b)<<8)+((c)<<16)+((d)<<24))
#define TEST_PASS	_TEST('P','A','S','S')
#define TEST_FAIL	_TEST('F','A','I','L')
#define TEST_STOP	_TEST('S','T','O','P')
#define TEST_VOID	_TEST('V','O','I','D')
#define TEST_TRAP	_TEST('T','R','A','P')
#define TEST_EXIT	_TEST('E','X','I','T')

#ifdef __ASSEMBLER__

#include <picos/asm.h>
#include <system/sysasm.h>

#else

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <picos/macros.h>

extern volatile char		TTY;
extern volatile char		TTYCHR[256];
extern volatile unsigned int	STOP;

static inline void tty_putc(unsigned char c)
{
    if (__builtin_constant_p(c))
	TTYCHR[c] = 0;
    else
	TTY = c;
}

static inline void tty_puts(const char *s)
{
    while (*s)
	TTY = *s++;
}

static inline noreturn void stop(unsigned int status)
{
    while (1)
	STOP = status;
    __builtin_unreachable();
}

noreturn void __assert_fail(const void *what, const void *file,
			    const void *func, unsigned long line);

#define assert(x)					     \
    do {						     \
	if (!__builtin_expect(!!(x),1))			     \
	    __assert_fail(#x, __FILE__, __func__, __LINE__); \
    } while (0)

#endif

#endif
