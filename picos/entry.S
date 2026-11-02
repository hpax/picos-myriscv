#include <picos/asm.h>
#include <picos/config.h>

begin_func _mtvec section=.init.irq global
	csrr	a1, mcause

	/*
	 * The IRQ bit is always followed by zeroes;
	 * thus, this always produces either -32 (interrupt) or 0 (trap.)
	 * Then OR back the IRQ or exception number (using OR, the IRQ bit
	 * is now irrelevant.)
	 */
	bclr	a0, a1, 31	/* Get the actual interrupt or trap number */
	cneg	a1, a0, a1	/* Negative if interrupt (no IRQ 0!) */

	/* Invoke handler */
	la	ra, trap_table
	lxsw	ra, (ra), a1

	/*
	 * Pass user_context in a1, this is a dead cycle anyway.
	 * There might be more useful things to pass instead.
	 */
	csrr	a1, myriscv.user_context

	/*
	 * Dispatch interrupt handler. Note that no registers need to
	 * be preserved (although either ra needs to be kept or a jump
	 * to __return_from_interrupt is required.
	 */
	jalr	ra, (ra)

	.globl __return_from_interrupt

__return_from_interrupt:
	lw	a0, ___runnable
	csrr	a1, myriscv.user_context
	ctz	a0, a0
	bne	a0, a1, .L_switch_task
	mret

.L_switch_task:
	csrr	a1, mepc
	sw	a1, (tp)
	csrw	myriscv.user_context, a0
	add.xu	tp, tp, 0
	lw	a1, (tp)
	csrw	mepc, a1
	mret
end _mtvec

begin_sdata ___runnable, 4, hot, global
	.long	2			/* Initial task 1 */
end __runnable
