.text

@ Timer 2 interrupt handler (gIntrTable slot 6). IntrMain stores the
@ interrupted return address at 0x030015A0 before dispatching; this loads it
@ into r0 and passes over an inline no$gba-style debug-message record
@ ("PRF %r0%") that an emulator can print. On hardware it only preserves r0
@ and returns.
	arm_func_start HandleTimer2Interrupt
HandleTimer2Interrupt: @ 0x080005B0
	stmfd sp!, {r0}
	ldr r0, _080005E8 @ =g_pTimer2DebugPc
	ldr r0, [r0]
	mov ip, ip
	b _080005E0
	.hword 0x6464
	.hword 0
	.ascii "PRF %r0%"
	.space 16
_080005E0:
	ldmfd sp!, {r0}
	bx lr
_080005E8: .4byte g_pTimer2DebugPc
	arm_func_end HandleTimer2Interrupt
