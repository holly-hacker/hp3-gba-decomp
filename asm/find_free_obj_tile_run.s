.text

@ First-fit search for a run of clear bits in an OBJ tile allocation bitmap
@ (bit set = in use, clear = free). r0: bitmap. r1: run length wanted, in
@ bits. r2: bit index to start searching from. Returns the index of the
@ first bit of the run, or 0xFFFF if no run fits below bit 0x400.
@ ARM-mode and only ever taken by address, never `bl` --
@ InstallIwramFindFreeObjTileRun relocates it into IWRAM via bios_CPUSet
@ (g_pFindFreeObjTileRunIwram).
@
@ r0 = start of the current candidate run, lr = bits still needed,
@ r2 = next bit to examine, ip = bit within the current byte.
@ A whole 0xFF byte is skipped at once, and a whole 0x00 byte counts as 8
@ free bits; otherwise bits are tested one at a time. A set bit abandons
@ the candidate and restarts just past it, unless a run of r1 bits could no
@ longer end within bit 0x400.
	arm_func_start FindFreeObjTileRun
FindFreeObjTileRun:                  @ 0x080063B4
	push {r4, r5, lr}
	mov r5, r0                @ r5 = bitmap
	mov r4, r1                @ r4 = run length wanted
.Lrestart:                    @ 0x080063C0
	mov lr, r4
	mov r0, r2                @ candidate starts at the next bit
	b .Lscan_byte
.Lbit_free:                   @ 0x080063CC
	sub lr, lr, #1
	cmp lr, #0
	ble .Lreturn              @ run complete, r0 = its start
.Lnext_bit:                   @ 0x080063D8
	add ip, ip, #1
	cmp ip, #7
	bls .Lcheck_bit
.Lscan_byte:                  @ 0x080063E4
	ldrb r1, [r5, r2, lsr #3]
	cmp r1, #0xff
	addeq r2, r2, #8          @ full byte in use
	beq .Lrun_broken
	cmp r1, #0
	bne .Lbyte_mixed
	add r2, r2, #8            @ empty byte: 8 more free bits
	sub lr, lr, #8
	cmp lr, #0
	bgt .Lscan_byte
	b .Lreturn
.Lbyte_mixed:                 @ 0x08006410
	and ip, r2, #7
.Lcheck_bit:                  @ 0x08006414
	add r2, r2, #1
	asr r3, r1, ip
	tst r3, #1
	beq .Lbit_free
.Lrun_broken:                 @ 0x08006424
	add r3, r2, r4
	cmp r3, #0x400
	bls .Lrestart
	mov r0, #0xff00
	add r0, r0, #0xff         @ 0xFFFF: not found
.Lreturn:                     @ 0x08006438
	pop {r4, r5, lr}
	bx lr
	arm_func_end FindFreeObjTileRun
