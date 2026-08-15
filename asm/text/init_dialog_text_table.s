.text

@ InitDialogTextTable(blobBase) -> 0.
@
@ Points the three decompressor globals DecompressDialogText reads
@ (gDialogTextBlobBase/OffsetTable/TreeNodes) at one language's
@ string-table blob, laid out as:
@   +0x00  u32 header  -- byte offset from blobBase to the offset table
@   +0x04  Huffman tree node table (header-4 bytes)
@   +header  u32[] offset table, one entry per string ID
@ Called by SetLanguage.
	thumb_func_start InitDialogTextTable
InitDialogTextTable: @ 0x08024EB8
	ldr r1, _08024ED0 @ =gDialogTextBlobBase
	str r0, [r1]
	adds r2, r0, #0
	ldm r2!, {r3}
	ldr r1, _08024ED4 @ =gDialogTextTreeNodes
	str r2, [r1]
	ldr r1, _08024ED8 @ =gDialogTextOffsetTable
	adds r0, r0, r3
	str r0, [r1]
	movs r0, #0
	bx lr
	.align 2, 0
_08024ED0: .4byte gDialogTextBlobBase
_08024ED4: .4byte gDialogTextTreeNodes
_08024ED8: .4byte gDialogTextOffsetTable
	thumb_func_end InitDialogTextTable
