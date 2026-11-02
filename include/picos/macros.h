#ifndef _PICOS_MACROS_H
#define _PICOS_MACROS_H 1

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define __unreachable()		__builtin_unreachable()
#define __likely(x)		__builtin_expect(!!(x), 1)
#define __unlikely(x)		__builtin_expect(!!(x), 0)

#define noreturn		__attribute__((__noreturn__))
#define __hot			__attribute__((__hot__))
#define __cold			__attribute__((__cold__))
#define __constfunc		__attribute__((__const__))
#define __purefunc		__attribute__((__pure__))
#define __section(x)		__attribute__((__section__(x)))
#define __always_inline		__attribute__((__always_inline__)) static inline

#define ARRAY_SIZE(__x)	(sizeof(__x) / sizeof((__x)[0]))
#define ARRAY_END(__x)	((__x) + ARRAY_SIZE(__x))
#define array_foreach(__iter, __array)		       \
    for (__auto_type __iter = &(__array)[0];	       \
	 __iter < ARRAY_END(__array); __iter++)

#endif /* _PICOS_MACROS_H */
