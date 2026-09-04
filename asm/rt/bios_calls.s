.text

@ Thumb wrappers around GBA BIOS SWI calls, one instruction pair (or triple)
@ each: load any fixed argument, svc #n, bx lr. bios_Mod reuses SWI 0x6
@ (Div) and returns the remainder (r1) in r0 instead of the quotient.
@ bios_VBlankIntrWait hardcodes r2 = 0 before SWI 0x5 (IntrWait's third
@ register is ignored by BIOS but agbcc's libc still sets it up here).

	thumb_func_start bios_ArcTan2
bios_ArcTan2: @ 0x08049E84
	svc #0xa
	bx lr

	thumb_func_start bios_BgAffineSet
bios_BgAffineSet: @ 0x08049E88
	svc #0xe
	bx lr

	thumb_func_start bios_CPUFastSet
bios_CPUFastSet: @ 0x08049E8C
	svc #0xc
	bx lr

	thumb_func_start bios_CPUSet
bios_CPUSet: @ 0x08049E90
	svc #0xb
	bx lr

	thumb_func_start bios_Div
bios_Div: @ 0x08049E94
	svc #6
	bx lr

	thumb_func_start bios_Mod
bios_Mod: @ 0x08049E98
	svc #6
	adds r0, r1, #0
	bx lr
	.align 2, 0

	thumb_func_start bios_HuffUnComp
bios_HuffUnComp: @ 0x08049EA0
	svc #0x13
	bx lr

	thumb_func_start bios_LZ77UnCompVRAM
bios_LZ77UnCompVRAM: @ 0x08049EA4
	svc #0x12
	bx lr

	thumb_func_start bios_LZ77UnCompWRAM
bios_LZ77UnCompWRAM: @ 0x08049EA8
	svc #0x11
	bx lr

	thumb_func_start bios_ObjAffineSet
bios_ObjAffineSet: @ 0x08049EAC
	svc #0xf
	bx lr

	thumb_func_start bios_RLUnCompVRAM
bios_RLUnCompVRAM: @ 0x08049EB0
	svc #0x15
	bx lr

	thumb_func_start bios_RLUnCompReadNormalWrite8bit
bios_RLUnCompReadNormalWrite8bit: @ 0x08049EB4
	svc #0x14
	bx lr

	thumb_func_start bios_Sqrt
bios_Sqrt: @ 0x08049EB8
	svc #8
	bx lr

	thumb_func_start bios_VBlankIntrWait
bios_VBlankIntrWait: @ 0x08049EBC
	movs r2, #0
	svc #5
	bx lr
	.align 2, 0
