#include <picos/asm.h>

begin_rodata __NULL, 4, section=.null, global
	.word 0
end __NULL

begin_func __start, section=.init.reset, global
	la	sp, ___stack_top
	la	gp, __global_pointer$
	la	tp, __tdata_start
	j	_start
end __start

begin_func _start, section=.init, global
	la	a0, __BSS_START__
	la	a1, __BSS_END__
	bge	a0, a1, 2f

1:
	lw	zero, (a0)
	lw	zero, 4(a0)
	lw	zero, 8(a0)
	lw	zero, 12(a0)
	lw	zero, 16(a0)
	lw	zero, 20(a0)
	lw	zero, 24(a0)
	lw	zero, 28(a0)
	add	a0, a0, 32
	blt	a0, a1, 1b

2:
	call	main
	.globl	exit
exit:
	j	_Exit
end _start
