.text

	thumb_func_start Mt19937RandSigned
Mt19937RandSigned: @ us:0x0803B47C, jp:0x0803B4E4
	push {r4, lr}
	adds r4, r0, #0
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	bl Mt19937Next
	ldr r1, _Mt19937RandSigned_L1 @ =0x00007FFF
	ands r1, r0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	lsls r0, r4, #1
	adds r0, #1
	muls r0, r1, r0
	lsrs r0, r0, #0xf
	subs r0, r0, r4
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_Mt19937RandSigned_L1: .4byte 0x00007FFF
	thumb_func_end Mt19937RandSigned
