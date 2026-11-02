#ifndef _ASSERT_H
#define _ASSERT_H 1

#include <picos/macros.h>

__noreturn void __assert_fail(const void *what, const void *file,
			      const void *func, unsigned long line);

#ifdef NDEBUG
# define assert(x) ((void)0)
#else
# define assert(x)					     \
    do {						     \
	if (!__builtin_expect(!!(x),1))			     \
	    __assert_fail(#x, __FILE__, __func__, __LINE__); \
    } while (0)
#endif

#endif /* _ASSERT_H */
