#ifndef _PICOS_ECALL_H
#define _PICOS_ECALL_H 1

#include <picos/macros.h>

#define __GET_MACRO9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _NAME, ...) _NAME

#define __ecall(...) __GET_MACRO9(__VA_ARGS__, __ecall8, __ecall7, \
				   __ecall6, __ecall5, __ecall4,   \
				   __ecall3, __ecall2, __ecall1,   \
				   __ecall0)(__VA_ARGS__)

#define ecall(...) __ecall(__VA_ARGS__)

__always_inline long
__ecall0(long __ncall)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0");
    asm volatile("ecall" : "=r" (__r_arg0) : : "memory");
    return __r_arg0;
}

__always_inline long
__ecall1(long __ncall, long __arg0)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 :
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall2(long __ncall, long __arg0, long __arg1)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg1;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1)
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall3(long __ncall, long __arg0, long __arg1, long __arg2)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2)
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall4(long __ncall, long __arg0, long __arg1, long __arg2,
	  long __arg3)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    register long __r_arg3  asm("a3") = __arg3;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2), "r" (__r_arg3)
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall5(long __ncall, long __arg0, long __arg1, long __arg2,
	  long __arg3, long __arg4)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    register long __r_arg3  asm("a3") = __arg3;
    register long __r_arg4  asm("a3") = __arg4;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2), "r" (__r_arg3),
		   "r" (__r_arg4)
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall6(long __ncall, long __arg0, long __arg1, long __arg2,
	  long __arg3, long __arg4, long __arg5)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    register long __r_arg3  asm("a3") = __arg3;
    register long __r_arg4  asm("a4") = __arg4;
    register long __r_arg5  asm("a5") = __arg5;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2), "r" (__r_arg3),
		   "r" (__r_arg4), "r" (__r_arg5)
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall7(long __ncall, long __arg0, long __arg1, long __arg2,
	  long __arg3, long __arg4, long __arg5, long __arg6)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    register long __r_arg3  asm("a3") = __arg3;
    register long __r_arg4  asm("a4") = __arg4;
    register long __r_arg5  asm("a5") = __arg5;
    register long __r_arg6  asm("a6") = __arg6;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2), "r" (__r_arg3),
		   "r" (__r_arg4), "r" (__r_arg5), "r" (__r_arg6),
		 : "memory");
    return __r_arg0;
}

__always_inline long
__ecall8(long __ncall, long __arg0, long __arg1, long __arg2,
	  long __arg3, long __arg4, long __arg5, long __arg6,
	  long __arg7)
{
    register long __r_ncall asm("t1") = __ncall;
    register long __r_arg0  asm("a0") = __arg0;
    register long __r_arg1  asm("a1") = __arg0;
    register long __r_arg2  asm("a2") = __arg2;
    register long __r_arg3  asm("a3") = __arg3;
    register long __r_arg4  asm("a4") = __arg4;
    register long __r_arg5  asm("a5") = __arg5;
    register long __r_arg6  asm("a6") = __arg6;
    register long __r_arg7  asm("a7") = __arg7;
    asm volatile("ecall"
		 : "+r" (__r_arg0)
		 : "r" (__r_arg1), "r" (__r_arg2), "r" (__r_arg3),
		   "r" (__r_arg4), "r" (__r_arg5), "r" (__r_arg6),
		   "r" (__r_arg7)
		 : "memory");
    return __r_arg0;
}

#endif /* _PICOS_ECALL_H */
