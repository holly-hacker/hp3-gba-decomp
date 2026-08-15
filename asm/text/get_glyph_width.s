.text

@ GetGlyphWidth(fontDescriptor, glyphCode) -> u8 pixel width.
@
@ fontDescriptor is a struct (fields as used here):
@   +0x02  u16 firstCode  -- first glyph code this font covers
@   +0x04  u16 lastCode   -- last glyph code this font covers
@   +0x0c  u32 widthTable -- byte-per-glyph width array, indexed by
@                            (glyphCode - firstCode)
@ If glyphCode falls outside [firstCode, lastCode], returns
@ widthTable[1] instead (a "missing glyph" fallback width).
	thumb_func_start GetGlyphWidth
GetGlyphWidth: @ 0x0802136C
	push {lr}
	adds r2, r0, #0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	movs r0, #0
	cmp r1, #0
	beq _08021396
	ldrh r3, [r2, #2]
	subs r1, r1, r3
	cmp r1, #0
	blt _08021392
	ldrh r0, [r2, #4]
	subs r0, r0, r3
	cmp r1, r0
	bgt _08021392
	ldr r0, [r2, #0xc]
	adds r0, r0, r1
	ldrb r0, [r0]
	b _08021396
_08021392:
	ldr r0, [r2, #0xc]
	ldrb r0, [r0, #1]
_08021396:
	pop {r1}
	bx r1
	.align 2, 0
	thumb_func_end GetGlyphWidth
