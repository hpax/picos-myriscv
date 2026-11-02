#include <system/system.h>

begin_func _Exit, hot, global
	bnez	a0, .L_fail
	finish	TEST_PASS
.L_fail:
	add	a0, a0, -1
	bnez	a0, .L_exit
	finish	TEST_FAIL
.L_exit:
	finish	TEST_EXIT
end _Exit
