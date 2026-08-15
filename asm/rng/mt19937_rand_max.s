.text

	thumb_func_start Mt19937RandMax
Mt19937RandMax: @ us:0x0803B434, jp:0x0803B49C
	push {r4, lr}
	adds r4, r0, #0
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	bl Mt19937Next
	ldr r1, _Mt19937RandMax_L1 @ =0x00007FFF
	ands r0, r1
	adds r4, #1
	muls r0, r4, r0
	lsls r0, r0, #1
	lsrs r0, r0, #0x10
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_Mt19937RandMax_L1: .4byte 0x00007FFF
	thumb_func_end Mt19937RandMax
