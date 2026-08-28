.text

@ libgcc's __divsi3 (dividend, divisor) -> dividend / divisor, signed.
@ Byte-identical to the _divsi3.o that agbcc's own libgcc.a builds; see
@ docs/compiler.md. On divisor==0 it calls __div0 and returns 0.
@
@ Takes the absolute value of both operands (remembering the sign of
@ their xor in ip), runs the same binary long division as __udivsi3,
@ then negates the result if that sign was negative.
	thumb_func_start __divsi3
__divsi3: @ us:0x0804A2FC, jp:0x0804A228
	cmp r1, #0
	beq __divsi3_L9
	push {r4}
	adds r4, r0, #0
	eors r4, r1
	mov ip, r4
	movs r3, #1
	movs r2, #0
	cmp r1, #0
	bpl __divsi3_L1
	negs r1, r1
__divsi3_L1:
	cmp r0, #0
	bpl __divsi3_L2
	negs r0, r0
__divsi3_L2:
	cmp r0, r1
	blo __divsi3_L6
	movs r4, #1
	lsls r4, r4, #0x1c
__divsi3_L3:
	cmp r1, r4
	bhs __divsi3_L4
	cmp r1, r0
	bhs __divsi3_L4
	lsls r1, r1, #4
	lsls r3, r3, #4
	b __divsi3_L3
__divsi3_L4:
	lsls r4, r4, #3
__divsi3_L5:
	cmp r1, r4
	bhs __divsi3_L10
	cmp r1, r0
	bhs __divsi3_L10
	lsls r1, r1, #1
	lsls r3, r3, #1
	b __divsi3_L5
__divsi3_L10:
	cmp r0, r1
	blo __divsi3_L7
	subs r0, r0, r1
	orrs r2, r3
__divsi3_L7:
	lsrs r4, r1, #1
	cmp r0, r4
	blo __divsi3_L8
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
__divsi3_L8:
	lsrs r4, r1, #2
	cmp r0, r4
	blo __divsi3_L11
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
__divsi3_L11:
	lsrs r4, r1, #3
	cmp r0, r4
	blo __divsi3_L12
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
__divsi3_L12:
	cmp r0, #0
	beq __divsi3_L6
	lsrs r3, r3, #4
	beq __divsi3_L6
	lsrs r1, r1, #4
	b __divsi3_L10
__divsi3_L6:
	adds r0, r2, #0
	mov r4, ip
	cmp r4, #0
	bpl __divsi3_L13
	negs r0, r0
__divsi3_L13:
	pop {r4}
	mov pc, lr
__divsi3_L9:
	push {lr}
	bl __div0
	movs r0, #0
	pop {pc}
	.align 2, 0
	thumb_func_end __divsi3
