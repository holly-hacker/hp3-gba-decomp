.text

	thumb_func_start Mt19937Next
Mt19937Next: @ us:0x0803B598, jp:0x0803B600
	push {lr}
	ldr r1, _Mt19937Next_L1 @ =gMt19937RemainingIndices
	ldr r0, [r1]
	subs r0, #1
	str r0, [r1]
	cmp r0, #0
	blt _Mt19937Next_L10
	ldr r1, _Mt19937Next_L2 @ =gMt19937DrawIndex
	ldr r0, [r1]
	adds r0, #1
	str r0, [r1]
	ldr r2, _Mt19937Next_L3 @ =gMt19937CurPtr
	ldr r0, [r2]
	ldm r0!, {r1}
	str r0, [r2]
	lsrs r0, r1, #0xb
	eors r1, r0
	lsls r0, r1, #7
	ldr r2, _Mt19937Next_L4 @ =0x9D2C5680
	ands r0, r2
	eors r1, r0
	lsls r0, r1, #0xf
	ldr r2, _Mt19937Next_L5 @ =0xEFC60000
	ands r0, r2
	eors r1, r0
	ldr r2, _Mt19937Next_L6 @ =gMt19937LastRollByte
	lsrs r0, r1, #0x12
	eors r0, r1
	strb r0, [r2]
	b _Mt19937Next_L11
	.align 2, 0
_Mt19937Next_L1: .4byte gMt19937RemainingIndices
_Mt19937Next_L2: .4byte gMt19937DrawIndex
_Mt19937Next_L3: .4byte gMt19937CurPtr
_Mt19937Next_L4: .4byte 0x9D2C5680
_Mt19937Next_L5: .4byte 0xEFC60000
_Mt19937Next_L6: .4byte gMt19937LastRollByte
_Mt19937Next_L10:
	bl Mt19937Regenerate
_Mt19937Next_L11:
	pop {r1}
	bx r1
	thumb_func_end Mt19937Next
