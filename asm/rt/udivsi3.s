.text

@ libgcc's __udivsi3 (dividend, divisor) -> dividend / divisor.
@ Byte-identical to the _udivsi3.o that agbcc's own libgcc.a builds;
@ see docs/compiler.md. Behaviour also checked by direct execution
@ against the real ROM code (Unicorn) -- 13 cases including 0,
@ divisor==dividend and 0xFFFFFFFF all matched Python's `//`.
@
@ Binary long division, accumulating the quotient in r2/r0. On
@ divisor==0 it calls __div0 and returns 0.
	thumb_func_start __udivsi3
__udivsi3: @ us:0x0804A464, jp:0x0804A390
	cmp r1, #0
	beq __udivsi3_L9
	movs r3, #1
	movs r2, #0
	push {r4}
	cmp r0, r1
	blo __udivsi3_L6
	movs r4, #1
	lsls r4, r4, #0x1c
__udivsi3_L1:
	cmp r1, r4
	bhs __udivsi3_L2
	cmp r1, r0
	bhs __udivsi3_L2
	lsls r1, r1, #4
	lsls r3, r3, #4
	b __udivsi3_L1
__udivsi3_L2:
	lsls r4, r4, #3
__udivsi3_L3:
	cmp r1, r4
	bhs __udivsi3_L4
	cmp r1, r0
	bhs __udivsi3_L4
	lsls r1, r1, #1
	lsls r3, r3, #1
	b __udivsi3_L3
__udivsi3_L4:
	cmp r0, r1
	blo __udivsi3_L5
	subs r0, r0, r1
	orrs r2, r3
__udivsi3_L5:
	lsrs r4, r1, #1
	cmp r0, r4
	blo __udivsi3_L7
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
__udivsi3_L7:
	lsrs r4, r1, #2
	cmp r0, r4
	blo __udivsi3_L8
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
__udivsi3_L8:
	lsrs r4, r1, #3
	cmp r0, r4
	blo __udivsi3_L10
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
__udivsi3_L10:
	cmp r0, #0
	beq __udivsi3_L6
	lsrs r3, r3, #4
	beq __udivsi3_L6
	lsrs r1, r1, #4
	b __udivsi3_L4
__udivsi3_L6:
	adds r0, r2, #0
	pop {r4}
	mov pc, lr
__udivsi3_L9:
	push {lr}
	bl __div0
	movs r0, #0
	pop {pc}
	thumb_func_end __udivsi3
