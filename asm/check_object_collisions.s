.text

@ Per-frame pairwise object collision check. r0: object count. r1: pointer to
@ an array of `Object *`. ARM-mode (see docs/compiler.md's "ARM-mode code"
@ section) and only ever taken by address, never `bl` -- InitObjectPool
@ relocates it into IWRAM via bios_CPUSet (g_pCheckObjectCollisionsIwram).
@
@ Each object carries two ObjectCollisionBox slots (include/object.h,
@ Object.aCollisionBoxes at +0xB0/+0xB8) and a matching 2-entry callback
@ array (Object.apfnCollisionCallback at +0xC8/+0xCC). For every ordered
@ pair (i, j>i) and each box slot (1 then 0), if slot `n` is active
@ (bState == 1) on object i, this resolves both objects' axis-aligned
@ boxes for that slot (position +0x36/+0x3A, box offsets flipped per
@ bAffineFlagsHigh's 0x10/0x20 bits) and tests them for overlap. On
@ overlap, gated on g_GameModeStackContext.dwCurrentGameMode == Overworld,
@ it calls object j's slot-`n` callback with object i as the argument,
@ then object i's slot-`n` callback with object j as the argument.
@ dwFlags bit 0x4000 on both objects skips the pair entirely (checked
@ before re-testing object j's own box-active flag).
	arm_func_start CheckObjectCollisions
CheckObjectCollisions:              @ 0x08005F10
	push {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #0x18
	str r0, [sp, #0x14]          @ sp[0x14] = object count
	mov r3, #0                   @ r3 = outer index i
	str r1, [sp, #0x10]          @ sp[0x10] = object pointer array
	cmp r3, r0
	bge .Louter_exit
.Louter_loop:                        @ 0x08005F2C
	mov r0, #1
	str r0, [sp, #0xc]            @ sp[0xc] = box slot index, starts at 1
	add r1, r3, r0                @ r1 = i+1
	str r1, [sp]                  @ sp[0] = inner loop start (i+1)
	ldr r2, [sp, #0x10]
	ldr r6, [r2, r3, lsl #2]       @ r6 = objects[i]
.Lslot_loop:                         @ 0x08005F44
	ldr r3, [sp, #0xc]
	ldr r0, [sp, #0xc]
	add r2, r6, r3, lsl #3         @ r2 = &objects[i]->aCollisionBoxes[slot]
	ldrsb r3, [r2, #0xb4]          @ ObjectCollisionBox.bState
	sub r8, r0, #1                 @ r8 = slot-1, preloaded for the next iteration
	cmp r3, #1
	bne .Lslot_continue            @ skip this slot: not active
	ldr r2, [r2, #0xb0]            @ r2 = ObjectCollisionBox.dwPackedOffsets
	ldrb r3, [r6, #0xd3]           @ bAffineFlagsHigh (X/Y-flip bits)
	ldrsh r1, [r6, #0x3a]          @ r1 = object i's integer Y
	tst r3, #0x20                  @ Y-flip
	beq .Lbox_a_no_yflip
	@ Y-flipped: swap+negate the top two packed bytes (byte3, byte2)
	sub r0, r1, r2, asr #24
	lsl r2, r2, #8
	str r0, [sp, #8]               @ sp[8]  = box A's high Y edge
	sub r1, r1, r2, asr #24
	str r1, [sp, #4]               @ sp[4]  = box A's low Y edge
	b .Lbox_a_merge_x
.Lbox_a_no_yflip:                    @ 0x08005F8C
	add r0, r1, r2, asr #24
	lsl r2, r2, #8
	str r0, [sp, #4]               @ sp[4]  = box A's low Y edge
	add r1, r1, r2, asr #24
	str r1, [sp, #8]               @ sp[8]  = box A's high Y edge
.Lbox_a_merge_x:                     @ 0x08005FA0
	lsl r2, r2, #8                 @ r2 now holds the low two packed bytes at its top
	ldrsh r1, [r6, #0x36]          @ r1 = object i's integer X
	tst r3, #0x10                  @ X-flip
	subne sl, r1, r2, asr #24
	lslne r2, r2, #8
	subne sb, r1, r2, asr #24
	addeq sb, r1, r2, asr #24
	lsleq r2, r2, #8
	addeq sl, r1, r2, asr #24       @ sb/sl = box A's low/high X edges
	ldr r7, [sp]                   @ r7 = inner loop index j
	ldr r1, [sp, #0x14]            @ r1 = object count
	ldr r2, [sp, #0xc]
	cmp r7, r1
	sub r8, r2, #1                  @ recompute r8 = slot-1 (clobbered above)
	bge .Lslot_continue
.Linner_loop:                        @ 0x08005FDC
	ldr r3, [sp, #0x10]
	ldr r2, [r6, #0xc]              @ object i's dwFlags
	ldr r4, [r3, r7, lsl #2]        @ r4 = objects[j]
	ldr r3, [r4, #0xc]              @ object j's dwFlags
	and r2, r2, r3
	tst r2, #0x4000                 @ both objects opted out of collision?
	bne .Linner_continue
	ldrsb r3, [r4, #0xb4]           @ objects[j]->aCollisionBoxes[slot].bState
	cmp r3, #1
	bne .Linner_continue
	ldr r2, [r4, #0xb0]             @ box B's dwPackedOffsets
	ldrb r3, [r4, #0xd3]            @ object j's bAffineFlagsHigh
	ldrsh r1, [r4, #0x3a]           @ object j's integer Y
	tst r3, #0x20
	subne ip, r1, r2, asr #24
	lslne r2, r2, #8
	subne lr, r1, r2, asr #24
	addeq lr, r1, r2, asr #24
	lsleq r2, r2, #8
	addeq ip, r1, r2, asr #24       @ ip/lr = box B's low/high Y edges
	lsl r2, r2, #8
	ldrsh r1, [r4, #0x36]           @ object j's integer X
	tst r3, #0x10
	subne r3, r1, r2, asr #24
	lslne r2, r2, #8
	subne r0, r1, r2, asr #24
	addeq r0, r1, r2, asr #24
	lsleq r2, r2, #8
	addeq r3, r1, r2, asr #24       @ r3/r0 = box B's low/high X edges
	cmp sb, r3                      @ X ranges overlap?
	cmpge r0, sl
	blt .Linner_continue
	ldmib sp, {r0, r1}              @ r0 = sp[4] (box A low Y), r1 = sp[8] (box A high Y)
	cmp r0, ip                      @ Y ranges overlap?
	cmpge lr, r1
	blt .Linner_continue
	ldr r3, .Lp_game_mode
	ldr r2, [r3]                    @ g_GameModeStackContext.dwCurrentGameMode
	cmp r2, #8                      @ Overworld
	bne .Linner_continue
	ldr r2, [sp, #0xc]              @ slot
	add r3, r4, #0xc8                @ &objects[j]->apfnCollisionCallback[0]
	lsl r5, r2, #2
	ldr r3, [r3, r5]                @ objects[j]->apfnCollisionCallback[slot]
	cmp r3, #0
	beq .Ldispatch_i_own_callback
	mov r0, r4                      @ self  = objects[j]
	mov r1, r6                      @ other = objects[i]
	mov lr, pc
	bx r3                           @ objects[j]->apfnCollisionCallback[slot](j, i)
.Ldispatch_i_own_callback:           @ 0x080060A4
	add r3, r6, #0xc8                @ &objects[i]->apfnCollisionCallback[0]
	ldr r3, [r3, r5]                @ objects[i]->apfnCollisionCallback[slot]
	cmp r3, #0
	beq .Linner_continue
	mov r0, r6                      @ self  = objects[i]
	mov r1, r4                      @ other = objects[j]
	mov lr, pc
	bx r3                           @ objects[i]->apfnCollisionCallback[slot](i, j)
.Linner_continue:                    @ 0x080060C4
	ldr r3, [sp, #0x14]
	add r7, r7, #1
	cmp r7, r3
	blt .Linner_loop
.Lslot_continue:                     @ 0x080060D4
	cmp r8, #0
	str r8, [sp, #0xc]
	bge .Lslot_loop                 @ do slot 0 after slot 1
	ldr r3, [sp]
	ldr r0, [sp, #0x14]
	cmp r3, r0
	b .Louter_continue
	.align 2, 0
.Lp_game_mode:                       @ 0x080060F0
	.4byte g_GameModeStackContext
.Louter_continue:                    @ 0x080060F4
	blt .Louter_loop
.Louter_exit:                        @ 0x080060F8
	add sp, sp, #0x18
	pop {r4, r5, r6, r7, r8, sb, sl, lr}
	bx lr
	arm_func_end CheckObjectCollisions

	@ Unexplained trailing word before the next region (DecompressLzRle at
	@ 0x08006108); identical bytes recur before SortObjectsByDepth's own
	@ next region. Ghidra's own function-boundary analysis excludes it from
	@ CheckObjectCollisions. Kept as raw data rather than reinterpreted as
	@ a real instruction -- purpose unconfirmed.
	.4byte 0xE12FFF1E              @ 0x08006104
