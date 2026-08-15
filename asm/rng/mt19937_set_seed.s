.text

	thumb_func_start Mt19937SetSeed
Mt19937SetSeed: @ us:0x0803B3AC, jp:0x0803B414
	push {lr}
	ldr r1, _Mt19937SetSeed_L1 @ =gMt19937SeedValue
	str r0, [r1]
	bl Mt19937SeedArray
	ldr r1, _Mt19937SetSeed_L2 @ =gMt19937RemainingIndices
	ldr r0, _Mt19937SetSeed_L3 @ =0x0000026F
	str r0, [r1]
	ldr r1, _Mt19937SetSeed_L4 @ =gMt19937CurPtr
	ldr r0, _Mt19937SetSeed_L5 @ =gMt19937StatePtr
	ldr r0, [r0]
	adds r0, #4
	str r0, [r1]
	pop {r0}
	bx r0
	.align 2, 0
_Mt19937SetSeed_L1: .4byte gMt19937SeedValue
_Mt19937SetSeed_L2: .4byte gMt19937RemainingIndices
_Mt19937SetSeed_L3: .4byte 0x0000026F
_Mt19937SetSeed_L4: .4byte gMt19937CurPtr
_Mt19937SetSeed_L5: .4byte gMt19937StatePtr
	thumb_func_end Mt19937SetSeed
