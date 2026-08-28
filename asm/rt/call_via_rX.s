.text

@ libgcc's interworking veneer table: one two-instruction stub per
@ register, `bx rN` then a `nop` pad. Thumb code that needs to branch to
@ an ARM-mode target through a register (rather than a fixed `bl`) `bl`s
@ into the matching `_call_via_rX` stub instead, which switches modes.
@ Byte-identical to agbcc's own _call_via_rX.o; see docs/compiler.md.
@ Live in this ROM: game code `bl`s into this table 169 times.
	thumb_func_start _call_via_r0
_call_via_r0: @ us:0x0804A2C0, jp:0x0804A1EC
	bx r0
	nop
	thumb_func_end _call_via_r0

	thumb_func_start _call_via_r1
_call_via_r1: @ us:0x0804A2C4, jp:0x0804A1F0
	bx r1
	nop
	thumb_func_end _call_via_r1

	thumb_func_start _call_via_r2
_call_via_r2: @ us:0x0804A2C8, jp:0x0804A1F4
	bx r2
	nop
	thumb_func_end _call_via_r2

	thumb_func_start _call_via_r3
_call_via_r3: @ us:0x0804A2CC, jp:0x0804A1F8
	bx r3
	nop
	thumb_func_end _call_via_r3

	thumb_func_start _call_via_r4
_call_via_r4: @ us:0x0804A2D0, jp:0x0804A1FC
	bx r4
	nop
	thumb_func_end _call_via_r4

	thumb_func_start _call_via_r5
_call_via_r5: @ us:0x0804A2D4, jp:0x0804A200
	bx r5
	nop
	thumb_func_end _call_via_r5

	thumb_func_start _call_via_r6
_call_via_r6: @ us:0x0804A2D8, jp:0x0804A204
	bx r6
	nop
	thumb_func_end _call_via_r6

	thumb_func_start _call_via_r7
_call_via_r7: @ us:0x0804A2DC, jp:0x0804A208
	bx r7
	nop
	thumb_func_end _call_via_r7

	thumb_func_start _call_via_r8
_call_via_r8: @ us:0x0804A2E0, jp:0x0804A20C
	bx r8
	nop
	thumb_func_end _call_via_r8

	thumb_func_start _call_via_r9
_call_via_r9: @ us:0x0804A2E4, jp:0x0804A210
	bx r9
	nop
	thumb_func_end _call_via_r9

	thumb_func_start _call_via_sl
_call_via_sl: @ us:0x0804A2E8, jp:0x0804A214
	bx sl
	nop
	thumb_func_end _call_via_sl

	thumb_func_start _call_via_fp
_call_via_fp: @ us:0x0804A2EC, jp:0x0804A218
	bx fp
	nop
	thumb_func_end _call_via_fp

	thumb_func_start _call_via_ip
_call_via_ip: @ us:0x0804A2F0, jp:0x0804A21C
	bx ip
	nop
	thumb_func_end _call_via_ip

	thumb_func_start _call_via_sp
_call_via_sp: @ us:0x0804A2F4, jp:0x0804A220
	bx sp
	nop
	thumb_func_end _call_via_sp

	thumb_func_start _call_via_lr
_call_via_lr: @ us:0x0804A2F8, jp:0x0804A224
	bx lr
	nop
	thumb_func_end _call_via_lr
