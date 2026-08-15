.text

@ DrawTextLine(arg0, arg1, arg2, maxWidth) -> value forwarded from
@ sub_080208B4 (the actual glyph-blit routine this hands off to; arg0/
@ arg1/arg2 are stored untouched and passed straight through to it, so
@ they're very likely pixel/attribute arguments for that routine
@ rather than anything DrawTextLine itself interprets -- not
@ independently confirmed here).
@
@ Word-wraps and measures ONE line's worth of glyph codes starting from
@ *[stack arg 5] (a caller-owned "current position" string-pointer
@ variable, dereferenced into r5), stopping once the accumulated pixel
@ width would exceed maxWidth (compared against the running width in
@ r3 throughout). Tracks the best-known wrap point in sb (a completed
@ word boundary: after a space, after a 0x2d hyphen that still fits, or
@ a hard break at 0x0a). Once a stopping point is chosen:
@  1. Copies the line's glyph codes (from the old position up to the
@     wrap point) into a local stack buffer, treating an 0x40-prefixed
@     escape pair as one atomic 2-byte unit rather than splitting it.
@  2. Writes the wrap point back through the caller's position
@     variable, so the next call resumes exactly there.
@  3. Calls sub_080208B4 with that buffer to actually draw the glyphs.
@  4. Skips a single trailing 0x0a and any run of spaces at the new
@     position, so the next line doesn't start with leftover
@     whitespace/the line-break marker itself.
@
@ Per-glyph-code decoding (shared with the width-measuring pass below):
@ a byte ==0x40 is an escape/macro prefix -- the following byte selects
@ a macro string from a pointer table at sTextMacroTable (index = byte-0x31),
@ which is itself walked (its own bytes can contain nested 0x40
@ escapes or >0xEF codes, recursing into MeasureMacroString) purely to
@ accumulate total pixel width -- the actual drawing happens later, in
@ sub_080208B4, once the whole line is finalized.
@ Outside of an escape, a byte >0xEF starts a two-byte extended glyph
@ code (combined as (byte0<<8)|byte1); either way, GetGlyphWidth(font,
@ glyphCode) gives the pixel width to accumulate, with the two font
@ descriptors at gTextRenderState[0x00]/[0x04] selected by the <=0xEF /
@ >0xEF split.
	thumb_func_start DrawTextLine
DrawTextLine: @ 0x08020714
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x58
	str r0, [sp, #0x44]  @ save arg0 (forwarded to sub_080208B4 at the end)
	str r1, [sp, #0x48]  @ save arg1 (forwarded)
	str r2, [sp, #0x4c]  @ save arg2 (forwarded)
	mov sl, r3            @ sl = maxWidth, checked against r3 throughout
	ldr r0, [sp, #0x78]   @ stack arg 5: &(caller's current-position variable)
	ldr r5, [r0]           @ r5 = current position (glyph-code read cursor)
	movs r1, #0
	mov sb, r1             @ sb = wrap point found so far (0 = none yet)
	movs r2, #0
	str r2, [sp, #0x50]      @ hyphen-candidate wrap point (0 = none)
	movs r3, #0              @ r3 = accumulated line width so far
	ldrb r0, [r5]
	cmp r0, #0
	beq _08020810
	cmp sb, sl
	bgt _0802080A
	b _08020804
_08020742:                     @ per-glyph-code dispatch (called in a loop below)
	ldrb r0, [r5]
	cmp r0, #0x40             @ 0x40 = escape/macro prefix
	bne _080207B0
	adds r5, #1
	ldr r1, _0802077C @ =sTextMacroTable  @ macro-string pointer table
	ldrb r0, [r5]
	subs r0, #0x31             @ macro index = code - 0x31
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r4, [r0]                @ r4 = selected macro string
	movs r6, #0                @ r6 = width accumulated within this macro
	ldrb r0, [r4]
	cmp r0, #0
	beq _080207AA
	mov r8, r1
	ldr r7, _08020780 @ =gTextRenderState
_08020762:                       @ walk the macro string, measuring only
	cmp r0, #0x40                @ (nested escape: recurse into another macro)
	bne _08020784
	adds r4, #1
	ldrb r0, [r4]
	subs r0, #0x31
	lsls r0, r0, #2
	add r0, r8
	ldr r0, [r0]
	str r3, [sp, #0x54]
	bl MeasureMacroString
	b _0802079E
	.align 2, 0
_0802077C: .4byte sTextMacroTable
_08020780: .4byte gTextRenderState
_08020784:
	ldrb r1, [r4]
	cmp r1, #0xef                  @ >0xef: two-byte extended glyph code
	bls _08020796
	lsls r1, r1, #8
	adds r4, #1
	ldrb r0, [r4]
	orrs r1, r0                    @ r1 = combined (byte0<<8)|byte1 code
	ldr r0, [r7, #4]                @ extended-range font descriptor
	b _08020798
_08020796:
	ldr r0, [r7]                    @ base-range font descriptor
_08020798:
	str r3, [sp, #0x54]
	bl GetGlyphWidth
_0802079E:
	adds r6, r6, r0                  @ accumulate this glyph's width
	ldr r3, [sp, #0x54]
	adds r4, #1
	ldrb r0, [r4]
	cmp r0, #0
	bne _08020762
_080207AA:
	adds r3, r3, r6                  @ fold the whole macro's width into the line total
	adds r1, r5, #1
	b _080207F8
_080207B0:
	cmp r0, #0x20                    @ plain space: always a valid wrap point
	beq _080207BE
	cmp r0, #0xf0                    @ 0xf0 0x00: also a valid wrap point
	bne _080207C0
	ldrb r0, [r5, #1]
	cmp r0, #0
	bne _080207C0
_080207BE:
	mov sb, r5
_080207C0:
	ldrb r1, [r5]
	lsls r2, r1, #0x18
	lsrs r0, r2, #0x18
	cmp r0, #0xef                    @ >0xef: two-byte extended glyph code
	bls _080207DC
	adds r5, #1
	ldrb r0, [r5]
	lsrs r1, r2, #0x10
	orrs r1, r0
	ldr r0, _080207D8 @ =gTextRenderState
	ldr r0, [r0, #4]                 @ extended-range font descriptor
	b _080207E0
	.align 2, 0
_080207D8: .4byte gTextRenderState
_080207DC:
	ldr r0, _080208B0 @ =gTextRenderState
	ldr r0, [r0]                      @ base-range font descriptor
_080207E0:
	str r3, [sp, #0x54]
	bl GetGlyphWidth
	ldr r3, [sp, #0x54]
	adds r3, r3, r0                   @ r3 = running line width
	ldrb r0, [r5]
	adds r1, r5, #1
	cmp r0, #0x2d                     @ hyphen: a wrap-point *candidate*
	bne _080207F8
	cmp r3, sl                        @ ...only remembered if it still fits
	bgt _080207F8
	str r1, [sp, #0x50]
_080207F8:
	adds r5, r1, #0
	ldrb r0, [r5]
	cmp r0, #0
	beq _08020810
	cmp r3, sl                        @ still under maxWidth? keep scanning
	bgt _0802080A
_08020804:
	cmp r0, #0xa                      @ 0x0a: hard line break
	bne _08020742
	mov sb, r5                        @ force the wrap point here
_0802080A:
	ldrb r0, [r5]
	cmp r0, #0
	bne _08020816
_08020810:
	cmp r3, sl
	bgt _08020816
	mov sb, r5                        @ reached end-of-string still under budget
_08020816:
	mov r0, sb
	cmp r0, #0
	bne _08020824
	ldr r1, [sp, #0x50]                @ no wrap point found: fall back to the
	cmp r1, #0                          @ hyphen candidate, if any
	beq _0802089C
	mov sb, r1
_08020824:
	add r1, sp, #4                     @ r1 = local line-buffer write cursor
	ldr r2, [sp, #0x78]
	ldr r5, [r2]                       @ r5 = start of this line (old position)
	cmp r5, sb
	beq _0802085A                      @ empty line: skip straight to the draw call
	ldr r2, [sp, #0x80]                 @ stack arg 6: &(remaining-chars budget)
	ldr r0, [r2]
	cmp r0, #0
	beq _0802085A
_08020836:                              @ copy [r5, sb) into the local buffer,
	ldrb r0, [r5]                        @ keeping an 0x40-prefixed pair intact
	cmp r0, #0x40
	bne _08020842
	strb r0, [r1]
	adds r5, #1
	adds r1, #1
_08020842:
	ldrb r0, [r5]
	strb r0, [r1]
	adds r5, #1
	adds r1, #1
	ldr r2, [sp, #0x80]
	ldr r0, [r2]
	subs r0, #1                        @ remaining-chars budget -= 1
	str r0, [r2]
	cmp r5, sb
	beq _0802085A
	cmp r0, #0
	bne _08020836
_0802085A:
	movs r0, #0
	strb r0, [r1]                      @ null-terminate the local buffer
	ldr r0, [sp, #0x78]
	str r5, [r0]                        @ write the wrap point back: next call resumes here
	ldr r0, [sp, #0x7c]                  @ stack arg 4: passed through as-is
	str r0, [sp]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x48]
	ldr r2, [sp, #0x4c]
	add r3, sp, #4                       @ &(the local, null-terminated line buffer)
	bl sub_080208B4                       @ the actual glyph-blit routine
	str r0, [sp, #0x44]
	ldr r2, [sp, #0x78]
	ldr r1, [r2]
	ldrb r0, [r1]
	cmp r0, #0xa                          @ consume a trailing hard-break marker
	bne _08020882                          @ so the next line doesn't see it again
	adds r0, r1, #1
	str r0, [r2]
_08020882:
	ldr r0, [sp, #0x78]
	ldr r2, [r0]
	ldrb r0, [r2]
	cmp r0, #0x20
	bne _0802089C
_0802088C:                                 @ also skip any run of leading spaces
	adds r1, r2, #0                         @ at the start of the next line
	adds r0, r1, #1
	ldr r2, [sp, #0x78]
	str r0, [r2]
	adds r2, r0, #0
	ldrb r0, [r1, #1]
	cmp r0, #0x20
	beq _0802088C
_0802089C:
	ldr r0, [sp, #0x44]
	add sp, #0x58
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080208B0: .4byte gTextRenderState
	thumb_func_end DrawTextLine
