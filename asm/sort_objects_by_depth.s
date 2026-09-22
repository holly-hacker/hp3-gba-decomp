.text

@ Sorts an array of Object pointers into draw order. r0: pointer array.
@ r1: object count. ARM-mode (see docs/compiler.md's "ARM-mode code"
@ section) and only ever taken by address, never `bl` -- InitObjectPool
@ relocates it into IWRAM via bios_CPUSet (g_pSortObjectsIwram).
@
@ Shell sort: an insertion sort repeated with shrinking gaps 21, 7, 3, 1
@ (Marcin Ciura's sequence), packed byte-wise into one 0x15070301 constant
@ and peeled off one byte at a time by shifting it left 8 bits each pass.
@ The sort key for each object is
@   ((bGfxSlotAndFlags & 0xC) << 22) | (bDepthSortBias << 16) - Y
@ (fields at +0xD5/+0x16/+0x3A) -- draw layer first, then the per-object
@ depth bias, then descending screen Y, all packed into one comparable
@ 32-bit value (the `+ 0x10000` bias just keeps the Y subtraction from
@ borrowing into the layer/bias bits for the Y range actually in play).
	arm_func_start SortObjectsByDepth
SortObjectsByDepth:                  @ 0x08006440
	push {r4, r5, r6, r7, r8, sb, sl, lr}
	ldr r3, .Lp_gap_seq
	mov r6, r0                     @ r6 = object pointer array
	mov sb, r1                     @ sb = object count
.Lgap_loop:                          @ 0x08006450
	lsr ip, r3, #0x18              @ ip = current gap (top byte of r3)
	cmp ip, sb
	mov r5, ip                     @ r5 = gap, kept live across the insertion loop
	lsl sl, r3, #8                 @ sl = remaining packed gaps, shifted up
	bhs .Lgap_done                  @ gap >= count: nothing to do this pass
.Linsert_loop:                       @ 0x08006464
	ldr r7, [r6, ip, lsl #2]        @ r7 = objects[i], i starts at the gap
	mov r4, ip                      @ r4 = insertion index, starts at i
	ldrb r3, [r7, #0xd5]            @ bGfxSlotAndFlags
	cmp ip, r5
	ldrb r2, [r7, #0x16]            @ bDepthSortBias
	add r8, ip, #1                  @ r8 = i+1, next outer index
	ldrsh r1, [r7, #0x3a]           @ integer Y
	lsl r3, r3, #0x16
	and r0, r3, #0x3000000          @ (bGfxSlotAndFlags & 0xC) << 22
	orr r0, r0, r2, lsl #16          @ | bDepthSortBias << 16
	add r3, r0, #0x10000
	rsb r0, r1, r3                  @ r0 = key(objects[i]) = above - Y
	blo .Lplace                      @ i < gap: nothing behind it to compare against
	rsb lr, r5, ip                   @ lr = i - gap
	b .Lcompare
	.align 2, 0
.Lp_gap_seq:                         @ 0x080064A0
	.4byte 0x15070301
.Lshift_down:                        @ 0x080064A4
	str ip, [r6, r4, lsl #2]        @ shift objects[k] up into the gap
	mov r4, lr                      @ r4 = k (the slot just vacated)
	cmp r4, r5
	blo .Lplace                      @ k < gap: no more predecessors, done
	rsb lr, r5, r4                   @ lr = k - gap, next predecessor
.Lcompare:                           @ 0x080064B8
	ldr ip, [r6, lr, lsl #2]        @ ip = objects[k - gap]
	ldrb r3, [ip, #0xd5]
	ldrb r2, [ip, #0x16]
	ldrsh r1, [ip, #0x3a]
	lsl r3, r3, #0x16
	and r3, r3, #0x3000000
	orr r3, r3, r2, lsl #16
	add r3, r3, #0x10000
	rsb r3, r1, r3                  @ r3 = key(objects[k - gap])
	cmp r0, r3                       @ key(objects[i]) < key(objects[k - gap])?
	blo .Lshift_down                 @ yes: predecessor sorts after i, shift it up
.Lplace:                             @ 0x080064E4
	mov ip, r8                       @ ip = i+1, for the next outer iteration
	str r7, [r6, r4, lsl #2]         @ drop objects[i] into its found slot
	cmp ip, sb
	blo .Linsert_loop
.Lgap_done:                          @ 0x080064F4
	subs r3, sl, #0                  @ any gaps left in the packed sequence?
	bne .Lgap_loop
	pop {r4, r5, r6, r7, r8, sb, sl, lr}
	bx lr
	arm_func_end SortObjectsByDepth

	@ Unexplained trailing word before the next region (LoadBgGraphicTiles_candidate
	@ at 0x08006508); identical bytes recur before CheckObjectCollisions's own
	@ next region (see asm/check_object_collisions.s). Kept as raw data rather
	@ than reinterpreted as a real instruction -- purpose unconfirmed.
	.4byte 0xE12FFF1E              @ 0x08006504
