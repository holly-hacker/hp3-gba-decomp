.text

	arm_func_start divsi3
divsi3: @ 0x0800027C
	ands r3, r1, #0x80000000
	rsbmi r1, r1, #0
	eor r3, r3, r0, asr #1
	cmp r0, #0
	rsbmi r0, r0, #0
	mov ip, lr
	bl udivsi3
	tst r3, #-0x80000000
	rsbne r0, r0, #0
	bx ip
	arm_func_end divsi3
