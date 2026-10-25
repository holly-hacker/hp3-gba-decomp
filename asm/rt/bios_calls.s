.text

@ Thumb wrappers around GBA BIOS SWI calls, one instruction pair (or triple)
@ each: load any fixed argument, svc #n, bx lr. bios_Mod reuses SWI 0x6
@ (Div) and returns the remainder (r1) in r0 instead of the quotient.
@ bios_VBlankIntrWait hardcodes r2 = 0 before SWI 0x5 (IntrWait's third
@ register is ignored by BIOS but agbcc's libc still sets it up here).

	thumb_func_start bios_ArcTan2
bios_ArcTan2:
	svc #0xa
	bx lr

	thumb_func_start bios_BgAffineSet
bios_BgAffineSet:
	svc #0xe
	bx lr

	thumb_func_start bios_CPUFastSet
bios_CPUFastSet:
	svc #0xc
	bx lr

	thumb_func_start bios_CPUSet
bios_CPUSet:
	svc #0xb
	bx lr

	thumb_func_start bios_Div
bios_Div:
	svc #6
	bx lr

	thumb_func_start bios_Mod
bios_Mod:
	svc #6
	adds r0, r1, #0
	bx lr
	.align 2, 0

	thumb_func_start bios_HuffUnComp
bios_HuffUnComp:
	svc #0x13
	bx lr

	thumb_func_start bios_LZ77UnCompVRAM
bios_LZ77UnCompVRAM:
	svc #0x12
	bx lr

	thumb_func_start bios_LZ77UnCompWRAM
bios_LZ77UnCompWRAM:
	svc #0x11
	bx lr

	thumb_func_start bios_ObjAffineSet
bios_ObjAffineSet:
	svc #0xf
	bx lr

	thumb_func_start bios_RLUnCompVRAM
bios_RLUnCompVRAM:
	svc #0x15
	bx lr

	thumb_func_start bios_RLUnCompReadNormalWrite8bit
bios_RLUnCompReadNormalWrite8bit:
	svc #0x14
	bx lr

	thumb_func_start bios_Sqrt
bios_Sqrt:
	svc #8
	bx lr

	thumb_func_start bios_VBlankIntrWait
bios_VBlankIntrWait:
	movs r2, #0
	svc #5
	bx lr
	.align 2, 0
