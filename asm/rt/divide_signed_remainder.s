.text

@ Hand-written ARM-mode signed divide/modulo: quotient in r0, remainder
@ stored through the pointer passed in r2. Not compiler runtime --
@ libgcc's are the Thumb routines in this directory.
	arm_func_start DivideSignedRemainder
DivideSignedRemainder: @ 0x080002A4
	stmdb sp!, {r2}
	ands r3, r1, #0x80000000
	rsbmi r1, r1, #0
	eor r3, r3, r0, asr #1
	cmp r0, #0
	rsbmi r0, r0, #0
	mov ip, lr
	bl DivideUnsignedWorker
	tst r3, #-0x80000000
	rsbne r0, r0, #0
	tst r3, #0x40000000
	rsbne r1, r1, #0
	ldm sp!, {r2}
	str r1, [r2]
	bx ip
	arm_func_end DivideSignedRemainder
