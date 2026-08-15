.text

	thumb_func_start Mt19937ChanceNoisy
Mt19937ChanceNoisy: @ us:0x0803B52C, jp:0x0803B594
	push {r4, lr}
	adds r4, r0, #0
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	bl Mt19937Next
	ldr r1, _Mt19937ChanceNoisy_L1 @ =0x04000006
	ldrh r1, [r1]
	adds r1, r1, r0
	ldr r0, _Mt19937ChanceNoisy_L2 @ =0x00007FFF
	ands r1, r0
	movs r0, #0x65
	muls r0, r1, r0
	lsrs r0, r0, #0xf
	cmp r4, r0
	blo _Mt19937ChanceNoisy_L3
	movs r0, #1
	b _Mt19937ChanceNoisy_L4
	.align 2, 0
_Mt19937ChanceNoisy_L1: .4byte 0x04000006
_Mt19937ChanceNoisy_L2: .4byte 0x00007FFF
_Mt19937ChanceNoisy_L3:
	movs r0, #0
_Mt19937ChanceNoisy_L4:
	pop {r4}
	pop {r1}
	bx r1
	thumb_func_end Mt19937ChanceNoisy
