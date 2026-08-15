.text

	thumb_func_start Mt19937Chance
Mt19937Chance: @ us:0x0803B4D4, jp:0x0803B53C
	push {r4, lr}
	adds r4, r0, #0
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	bl Mt19937Next
	ldr r1, _Mt19937Chance_L1 @ =0x00007FFF
	ands r1, r0
	movs r0, #0x65
	muls r0, r1, r0
	lsrs r0, r0, #0xf
	cmp r4, r0
	blo _Mt19937Chance_L2
	movs r0, #1
	b _Mt19937Chance_L3
	.align 2, 0
_Mt19937Chance_L1: .4byte 0x00007FFF
_Mt19937Chance_L2:
	movs r0, #0
_Mt19937Chance_L3:
	pop {r4}
	pop {r1}
	bx r1
	thumb_func_end Mt19937Chance
