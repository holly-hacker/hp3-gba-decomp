.text

	thumb_func_start Mt19937RandRange
Mt19937RandRange: @ us:0x0803B3E0, jp:0x0803B448
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	cmp r4, r5
	beq _Mt19937RandRange_L2
	bl Mt19937Next
	ldr r1, _Mt19937RandRange_L1 @ =0x00007FFF
	ands r1, r0
	subs r0, r5, r4
	adds r0, #1
	muls r0, r1, r0
	asrs r0, r0, #0xf
	adds r0, r4, r0
	b _Mt19937RandRange_L3
	.align 2, 0
_Mt19937RandRange_L1: .4byte 0x00007FFF
_Mt19937RandRange_L2:
	adds r0, r4, #0
_Mt19937RandRange_L3:
	pop {r4, r5}
	pop {r1}
	bx r1
	thumb_func_end Mt19937RandRange
