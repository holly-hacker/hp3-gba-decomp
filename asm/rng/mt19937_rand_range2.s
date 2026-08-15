.text

	thumb_func_start Mt19937RandRange2
Mt19937RandRange2: @ us:0x0803B40C, jp:0x0803B474
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	bl Mt19937Next2
	ldr r1, _Mt19937RandRange2_L1 @ =0x00007FFF
	ands r1, r0
	subs r4, r4, r5
	adds r4, #1
	adds r0, r1, #0
	muls r0, r4, r0
	asrs r0, r0, #0xf
	adds r5, r5, r0
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_Mt19937RandRange2_L1: .4byte 0x00007FFF
	thumb_func_end Mt19937RandRange2
