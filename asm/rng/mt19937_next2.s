.text

	thumb_func_start Mt19937Next2
Mt19937Next2: @ us:0x0803B5F4, jp:0x0803B65C
	push {lr}
	ldr r1, _Mt19937Next2_L1 @ =gMt19937RemainingIndices2
	ldr r0, [r1]
	subs r0, #1
	str r0, [r1]
	ldr r2, _Mt19937Next2_L2 @ =gMt19937CurPtr2
	cmp r0, #0
	bge _Mt19937Next2_L10
	ldr r0, _Mt19937Next2_L3 @ =0x0000026F
	str r0, [r1]
	ldr r0, _Mt19937Next2_L4 @ =gMt19937StatePtr
	ldr r0, [r0]
	adds r0, #4
	str r0, [r2]
_Mt19937Next2_L10:
	ldr r1, [r2]
	ldm r1!, {r0}
	str r1, [r2]
	lsrs r1, r0, #0xb
	eors r0, r1
	lsls r1, r0, #7
	ldr r2, _Mt19937Next2_L5 @ =0x9D2C5680
	ands r1, r2
	eors r0, r1
	lsls r1, r0, #0xf
	ldr r2, _Mt19937Next2_L6 @ =0xEFC60000
	ands r1, r2
	eors r0, r1
	lsrs r1, r0, #0x12
	eors r0, r1
	pop {r1}
	bx r1
	.align 2, 0
_Mt19937Next2_L1: .4byte gMt19937RemainingIndices2
_Mt19937Next2_L2: .4byte gMt19937CurPtr2
_Mt19937Next2_L3: .4byte 0x0000026F
_Mt19937Next2_L4: .4byte gMt19937StatePtr
_Mt19937Next2_L5: .4byte 0x9D2C5680
_Mt19937Next2_L6: .4byte 0xEFC60000
	thumb_func_end Mt19937Next2
