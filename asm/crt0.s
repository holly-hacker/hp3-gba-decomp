.text

	arm_func_start crt0
crt0: @ 0x080000C0
	@ set up IRQ-mode stack
	mov r0, #0x12
	msr cpsr_fc, r0
	ldr sp, _080000F8 @ =gIrqStackTop

	@ set up system-mode stack
	mov r0, #0x1f
	msr cpsr_fc, r0
	ldr sp, _080000F4 @ =gSystemStackTop

	@ install interrupt handler
	ldr r1, _080000FC @ =gIntrVectorPtr
	add r0, pc, #0x50 @ =IntrMain
	str r0, [r1]

	@ switch to thumb
	add r0, pc, #0x1 @ =crt0_CallMain
	bx r0
	arm_func_end crt0

	thumb_func_start crt0_CallMain
crt0_CallMain: @ 0x080000EC
	ldr r1, _08000100 @ =gMainEntryPoint
	mov lr, pc
	bx r1
	b crt0
	.align 2, 0
_080000F4: .4byte gSystemStackTop
_080000F8: .4byte gIrqStackTop
_080000FC: .4byte gIntrVectorPtr
_08000100: .4byte gMainEntryPoint
	thumb_func_end crt0_CallMain
