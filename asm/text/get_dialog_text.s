.text

@ GetDialogText(stringId) -> glyph-code string pointer, or NULL on
@ failure (buffer overflow / no language blob installed yet).
@ Thin wrapper: decompresses into a fixed 0x400-byte scratch buffer at
@ gDialogTextScratchBuf and returns that buffer's pointer.
	thumb_func_start GetDialogText
GetDialogText: @ 0x080425E4
	push {r4, lr}
	ldr r4, _080425FC @ =gDialogTextScratchBuf
	ldr r1, [r4]        @ r1 = scratch buffer pointer
	movs r2, #0x80
	lsls r2, r2, #3      @ r2 = buffer size (0x400)
	bl DecompressDialogText
	cmp r0, #0           @ 0 = success
	beq _08042600
	movs r0, #0           @ failure: return NULL
	b _08042602
	.align 2, 0
_080425FC: .4byte gDialogTextScratchBuf
_08042600:
	ldr r0, [r4]           @ success: return the buffer pointer
_08042602:
	pop {r4}
	pop {r1}
	bx r1
	thumb_func_end GetDialogText
