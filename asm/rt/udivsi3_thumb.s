.text

@ udivsi3_thumb(dividend, divisor) -> dividend / divisor (unsigned).
@ Confirmed by direct execution against the real ROM code (Unicorn),
@ same as umodsi3 -- 13 test cases including 0, divisor==dividend, and
@ 0xFFFFFFFF all matched Python's `//` exactly.
@
@ The quotient-returning sibling of umodsi3 (same binary-long-division
@ shape, same divide-by-zero handling, but accumulates and returns the
@ quotient in r2/r0 instead of reducing r0 to the remainder) -- a
@ separate routine, not a shared umodsi3 code path, so the ROM pays for
@ near-duplicate logic twice rather than a single combined divmod.
@ Called from 6 sites scattered across the ROM, unrelated to the RNG --
@ general-purpose runtime library code. Named `udivsi3_thumb` (not
@ `udivsi3`, already used by the unrelated ARM-mode routine at
@ 0x080002E0) after GCC's runtime symbol for this operation, matching
@ the existing divsi3/udivsi3/divmodsi4/umodsi3 convention -- not a
@ claim about the actual compiler, which is still unconfirmed (see
@ docs/compiler.md).
	thumb_func_start udivsi3_thumb
udivsi3_thumb: @ us:0x0804A464, jp:0x0804A390
	cmp r1, #0
	beq _udivsi3_thumb_L9
	movs r3, #1
	movs r2, #0
	push {r4}
	cmp r0, r1
	blo _udivsi3_thumb_L6
	movs r4, #1
	lsls r4, r4, #0x1c
_udivsi3_thumb_L1:
	cmp r1, r4
	bhs _udivsi3_thumb_L2
	cmp r1, r0
	bhs _udivsi3_thumb_L2
	lsls r1, r1, #4
	lsls r3, r3, #4
	b _udivsi3_thumb_L1
_udivsi3_thumb_L2:
	lsls r4, r4, #3
_udivsi3_thumb_L3:
	cmp r1, r4
	bhs _udivsi3_thumb_L4
	cmp r1, r0
	bhs _udivsi3_thumb_L4
	lsls r1, r1, #1
	lsls r3, r3, #1
	b _udivsi3_thumb_L3
_udivsi3_thumb_L4:
	cmp r0, r1
	blo _udivsi3_thumb_L5
	subs r0, r0, r1
	orrs r2, r3
_udivsi3_thumb_L5:
	lsrs r4, r1, #1
	cmp r0, r4
	blo _udivsi3_thumb_L7
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
_udivsi3_thumb_L7:
	lsrs r4, r1, #2
	cmp r0, r4
	blo _udivsi3_thumb_L8
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
_udivsi3_thumb_L8:
	lsrs r4, r1, #3
	cmp r0, r4
	blo _udivsi3_thumb_L10
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
_udivsi3_thumb_L10:
	cmp r0, #0
	beq _udivsi3_thumb_L6
	lsrs r3, r3, #4
	beq _udivsi3_thumb_L6
	lsrs r1, r1, #4
	b _udivsi3_thumb_L4
_udivsi3_thumb_L6:
	adds r0, r2, #0
	pop {r4}
	mov pc, lr
_udivsi3_thumb_L9:
	push {lr}
	bl DivZeroHandler
	movs r0, #0
	pop {pc}
	thumb_func_end udivsi3_thumb
