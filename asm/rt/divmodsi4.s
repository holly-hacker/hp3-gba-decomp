.text

	arm_func_start divmodsi4
divmodsi4: @ 0x080002A4
	stmdb sp!, {r2}
	ands r3, r1, #0x80000000
	rsbmi r1, r1, #0
	eor r3, r3, r0, asr #1
	cmp r0, #0
	rsbmi r0, r0, #0
	mov ip, lr
	bl udivsi3
	tst r3, #-0x80000000
	rsbne r0, r0, #0
	tst r3, #0x40000000
	rsbne r1, r1, #0
	ldm sp!, {r2}
	str r1, [r2]
	bx ip
	arm_func_end divmodsi4
