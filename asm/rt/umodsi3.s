.text

@ umodsi3(dividend, divisor) -> dividend % divisor (unsigned).
@ Confirmed by direct execution against the real ROM code (Unicorn),
@ not just read from the disassembly -- 13 test cases including 0,
@ divisor==dividend, and 0xFFFFFFFF all matched Python's `%` exactly.
@ Binary long division: builds the quotient bit-by-bit into r2/r3
@ (used only internally -- this routine never returns the quotient),
@ reducing r0 by successive shifted copies of the divisor until it's
@ the final remainder.
@
@ Named after GCC's runtime symbol for this exact operation, matching
@ the existing divsi3/udivsi3/divmodsi4 convention in this directory --
@ not a claim about the actual compiler, which is still unconfirmed
@ (see docs/compiler.md).
@
@ Thumb-mode; a separate routine from the ARM-mode division cluster at
@ 0x080002E0 (divsi3/udivsi3/divmodsi4), presumably because Thumb code
@ can't `bl` directly into ARM-mode code without an interworking
@ veneer. On divisor==0, calls DivZeroHandler (a no-op) and returns 0.
	thumb_func_start umodsi3
umodsi3: @ us:0x0804A4DC, jp:0x0804A408
	cmp r1, #0
	beq _umodsi3_L9
	movs r3, #1
	cmp r0, r1
	bhs _umodsi3_L1
	mov pc, lr
_umodsi3_L1:
	push {r4}
	movs r4, #1
	lsls r4, r4, #0x1c
_umodsi3_L2:
	cmp r1, r4
	bhs _umodsi3_L3
	cmp r1, r0
	bhs _umodsi3_L3
	lsls r1, r1, #4
	lsls r3, r3, #4
	b _umodsi3_L2
_umodsi3_L3:
	lsls r4, r4, #3
_umodsi3_L4:
	cmp r1, r4
	bhs _umodsi3_L5
	cmp r1, r0
	bhs _umodsi3_L5
	lsls r1, r1, #1
	lsls r3, r3, #1
	b _umodsi3_L4
_umodsi3_L5:
	movs r2, #0
	cmp r0, r1
	blo _umodsi3_L6
	subs r0, r0, r1
_umodsi3_L6:
	lsrs r4, r1, #1
	cmp r0, r4
	blo _umodsi3_L7
	subs r0, r0, r4
	mov ip, r3
	movs r4, #1
	rors r3, r4
	orrs r2, r3
	mov r3, ip
_umodsi3_L7:
	lsrs r4, r1, #2
	cmp r0, r4
	blo _umodsi3_L8
	subs r0, r0, r4
	mov ip, r3
	movs r4, #2
	rors r3, r4
	orrs r2, r3
	mov r3, ip
_umodsi3_L8:
	lsrs r4, r1, #3
	cmp r0, r4
	blo _umodsi3_L10
	subs r0, r0, r4
	mov ip, r3
	movs r4, #3
	rors r3, r4
	orrs r2, r3
	mov r3, ip
_umodsi3_L10:
	mov ip, r3
	cmp r0, #0
	beq _umodsi3_L11
	lsrs r3, r3, #4
	beq _umodsi3_L11
	lsrs r1, r1, #4
	b _umodsi3_L5
_umodsi3_L11:
	movs r4, #0xe
	lsls r4, r4, #0x1c
	ands r2, r4
	bne _umodsi3_L12
	pop {r4}
	mov pc, lr
_umodsi3_L12:
	mov r3, ip
	movs r4, #3
	rors r3, r4
	tst r2, r3
	beq _umodsi3_L13
	lsrs r4, r1, #3
	adds r0, r0, r4
_umodsi3_L13:
	mov r3, ip
	movs r4, #2
	rors r3, r4
	tst r2, r3
	beq _umodsi3_L14
	lsrs r4, r1, #2
	adds r0, r0, r4
_umodsi3_L14:
	mov r3, ip
	movs r4, #1
	rors r3, r4
	tst r2, r3
	beq _umodsi3_L15
	lsrs r4, r1, #1
	adds r0, r0, r4
_umodsi3_L15:
	pop {r4}
	mov pc, lr
_umodsi3_L9:
	push {lr}
	bl DivZeroHandler
	movs r0, #0
	pop {pc}
	thumb_func_end umodsi3
