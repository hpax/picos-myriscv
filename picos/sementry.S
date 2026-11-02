#include <picos/asm.h>
#include <picos/irq.h>

/*
 * The part of the semaphore code that is executed in user mode
 */
begin_func __sem_down_slow_asm, hot, global
	csrr	t6, cycle
	lw	t5, ___runnable
	csrr	t4, myriscv.user_context
	bclr	t5, t5, t4
	sw	t5, ___runnable, t4
	sw	a0, 4(tp)		/* Blocker */
	trapeq	CTRAP_SCHEDULE, zero, zero
	sw	zero, 4(tp)		/* Mark as no longer blocked */

__sem_yield_resume:
	csrr	a0, cycle
	sub	a0, a0, t6
	jr	t0			/* Return */
end __sem_down_slow_asm

begin_func __sem_up_slow_asm, hot, global
	lw	t5, ___runnable
	ctz	t6, t1			/* Lowest waiter in the mask */
	bclr	t1, t1, t6		/* Remove it from the mask */
	bset	t5, t5, t6		/* Add it to the runnable set */
	sw	t5, ___runnable, t4
	csrr	t5, myriscv.user_context
	trapltu	CTRAP_SEM_YIELD, t6, t5
	sc.w	a0, t1, (a0)		/* a0 <- 0 */
	jr	t0			/* Return */
end __sem_up_slow_asm

/*
 * The part of the semaphore code that is executed in machine mode
 */
begin_func ___sem_up_yield, hot, global
	/* a1 = task number */
	/* Save the initial timestamp; 20 is a fudge factor */
	csrr	a0, cycle
	add.ux	t6, a0, -20
	/* Restart at __sem_yield_resume */
	la	a0, __sem_yield_resume
	csrw	mepc, a0
	ret
end ___sem_up_yield

	.globl	___ctrap_1
___ctrap_1 = ___sem_up_yield
