.text

@ libgcc's __div0, the divide-by-zero hook the division routines call
@ before returning 0. This is the `_dvmd_tls` no-op build of it: it
@ returns immediately. Byte-identical to agbcc's own _dvmd_tls.o; see
@ docs/compiler.md.
	thumb_func_start __div0
__div0: @ us:0x0804A390, jp:0x0804A2BC
	mov pc, lr
	.align 2, 0
	thumb_func_end __div0
