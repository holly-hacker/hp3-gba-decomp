.text

	thumb_func_start Mt19937Regenerate
Mt19937Regenerate: @ us:0x0803B1B8, jp:0x0803B220
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	ldr r2, _Mt19937Regenerate_L1 @ =gMt19937StatePtr
	ldr r4, [r2]
	movs r0, #8
	adds r0, r0, r4
	mov ip, r0
	ldr r1, _Mt19937Regenerate_L2 @ =0x00000634
	adds r7, r4, r1
	ldr r0, _Mt19937Regenerate_L3 @ =gMt19937RemainingIndices
	ldr r3, [r0]
	movs r1, #1
	rsbs r1, r1, #0
	mov sl, r2
	adds r2, r0, #0
	ldr r6, _Mt19937Regenerate_L4 @ =gMt19937CurPtr
	cmp r3, r1
	bge _Mt19937Regenerate_L11
	ldr r0, _Mt19937Regenerate_L5 @ =gMt19937SeedValue
	ldr r1, [r0]
	movs r0, #1
	orrs r1, r0
	movs r0, #0
	str r0, [r2]
	adds r3, r4, #0
	stm r3!, {r1}
	ldr r0, _Mt19937Regenerate_L6 @ =0x0000026F
	ldr r5, _Mt19937Regenerate_L7 @ =0x00010DCD
_Mt19937Regenerate_L10:
	muls r1, r5, r1
	stm r3!, {r1}
	subs r0, #1
	cmp r0, #0
	bne _Mt19937Regenerate_L10
_Mt19937Regenerate_L11:
	ldr r0, _Mt19937Regenerate_L6 @ =0x0000026F
	str r0, [r2]
	mov r1, sl
	ldr r0, [r1]
	adds r1, r0, #4
	str r1, [r6]
	ldr r3, [r0]
	ldr r2, [r0, #4]
	movs r5, #0xe3
	movs r0, #0x80
	lsls r0, r0, #0x18
	mov r8, r0
	ldr r6, _Mt19937Regenerate_L8 @ =0x7FFFFFFF
_Mt19937Regenerate_L12:
	mov r1, r8
	ands r3, r1
	adds r0, r2, #0
	ands r0, r6
	orrs r0, r3
	lsrs r0, r0, #1
	ldm r7!, {r1}
	adds r3, r4, #0
	adds r4, #4
	eors r1, r0
	movs r0, #1
	ands r0, r2
	cmp r0, #0
	beq _Mt19937Regenerate_L13
	ldr r0, _Mt19937Regenerate_L9 @ =0x9908B0DF
	eors r1, r0
_Mt19937Regenerate_L13:
	str r1, [r3]
	adds r3, r2, #0
	mov r0, ip
	adds r0, #4
	mov ip, r0
	subs r0, #4
	ldm r0!, {r2}
	subs r5, #1
	cmp r5, #0
	bne _Mt19937Regenerate_L12
	mov r1, sl
	ldr r7, [r1]
	movs r5, #0xc6
	lsls r5, r5, #1
	movs r0, #0x80
	lsls r0, r0, #0x18
	mov sb, r0
	ldr r1, _Mt19937Regenerate_L8 @ =0x7FFFFFFF
	mov r8, r1
_Mt19937Regenerate_L14:
	mov r0, sb
	ands r3, r0
	adds r0, r2, #0
	mov r1, r8
	ands r0, r1
	orrs r0, r3
	lsrs r0, r0, #1
	ldm r7!, {r1}
	adds r3, r4, #0
	adds r4, #4
	eors r1, r0
	movs r6, #1
	adds r0, r2, #0
	ands r0, r6
	cmp r0, #0
	beq _Mt19937Regenerate_L15
	ldr r0, _Mt19937Regenerate_L9 @ =0x9908B0DF
	eors r1, r0
_Mt19937Regenerate_L15:
	str r1, [r3]
	adds r3, r2, #0
	mov r0, ip
	adds r0, #4
	mov ip, r0
	subs r0, #4
	ldm r0!, {r2}
	subs r5, #1
	cmp r5, #0
	bne _Mt19937Regenerate_L14
	mov r1, sl
	ldr r0, [r1]
	ldr r2, [r0]
	movs r1, #0x80
	lsls r1, r1, #0x18
	ands r1, r3
	ldr r0, _Mt19937Regenerate_L8 @ =0x7FFFFFFF
	ands r0, r2
	orrs r0, r1
	lsrs r0, r0, #1
	ldr r1, [r7]
	eors r1, r0
	str r1, [r4]
	adds r0, r2, #0
	ands r0, r6
	cmp r0, #0
	beq _Mt19937Regenerate_L16
	ldr r0, _Mt19937Regenerate_L9 @ =0x9908B0DF
	eors r1, r0
	str r1, [r4]
_Mt19937Regenerate_L16:
	lsrs r0, r2, #0xb
	eors r2, r0
	lsls r0, r2, #7
	ldr r1, _Mt19937Regenerate_L17 @ =0x9D2C5680
	ands r0, r1
	eors r2, r0
	lsls r0, r2, #0xf
	ldr r1, _Mt19937Regenerate_L18 @ =0xEFC60000
	ands r0, r1
	eors r2, r0
	lsrs r0, r2, #0x12
	eors r2, r0
	adds r0, r2, #0
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_Mt19937Regenerate_L1: .4byte gMt19937StatePtr
_Mt19937Regenerate_L2: .4byte 0x00000634
_Mt19937Regenerate_L3: .4byte gMt19937RemainingIndices
_Mt19937Regenerate_L4: .4byte gMt19937CurPtr
_Mt19937Regenerate_L5: .4byte gMt19937SeedValue
_Mt19937Regenerate_L6: .4byte 0x0000026F
_Mt19937Regenerate_L7: .4byte 0x00010DCD
_Mt19937Regenerate_L8: .4byte 0x7FFFFFFF
_Mt19937Regenerate_L9: .4byte 0x9908B0DF
_Mt19937Regenerate_L17: .4byte 0x9D2C5680
_Mt19937Regenerate_L18: .4byte 0xEFC60000
	thumb_func_end Mt19937Regenerate
