.text

	thumb_func_start Mt19937SeedArray
Mt19937SeedArray: @ us:0x0803B560, jp:0x0803B5C8
	push {lr}
	adds r2, r0, #0
	movs r0, #1
	orrs r2, r0
	ldr r0, _Mt19937SeedArray_L1 @ =gMt19937StatePtr
	ldr r3, [r0]
	ldr r1, _Mt19937SeedArray_L2 @ =gMt19937RemainingIndices
	movs r0, #0
	str r0, [r1]
	stm r3!, {r2}
	ldr r0, _Mt19937SeedArray_L3 @ =0x0000026F
	ldr r1, _Mt19937SeedArray_L4 @ =0x00010DCD
_Mt19937SeedArray_L10:
	muls r2, r1, r2
	stm r3!, {r2}
	subs r0, #1
	cmp r0, #0
	bne _Mt19937SeedArray_L10
	pop {r0}
	bx r0
	.align 2, 0
_Mt19937SeedArray_L1: .4byte gMt19937StatePtr
_Mt19937SeedArray_L2: .4byte gMt19937RemainingIndices
_Mt19937SeedArray_L3: .4byte 0x0000026F
_Mt19937SeedArray_L4: .4byte 0x00010DCD
	thumb_func_end Mt19937SeedArray
