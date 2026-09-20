.text

@ Hand-written ARM-mode: sets the CPSR I bit (disables IRQs), preserving r0.
	arm_func_start DisableIrq
DisableIrq: @ 0x0800011C
	stmfd sp!, {r0}
	mrs r0, cpsr
	orr r0, r0, #0x80
	msr cpsr_fc, r0
	ldmfd sp!, {r0}
	bx lr
	arm_func_end DisableIrq
