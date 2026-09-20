.text

@ Hand-written ARM-mode: clears the CPSR I bit (enables IRQs), preserving r0.
	arm_func_start EnableIrq
EnableIrq: @ 0x08000104
	stmfd sp!, {r0}
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_fc, r0
	ldmfd sp!, {r0}
	bx lr
	arm_func_end EnableIrq
