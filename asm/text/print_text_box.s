.text

@ PrintTextBox(arg0, maxWidth, posArg1, posArg2) -> DrawTextLine's
@ return value from the final call made (arg meanings for arg0/
@ posArg1/posArg2/the return value follow DrawTextLine's own, which
@ aren't all independently confirmed -- see get_glyph_width.s and
@ draw_text_line.s for what is confirmed there).
@ Multi-line wrapper around DrawTextLine: calls it once per line, using
@ a stack out-param to learn where the next line should resume, and
@ advancing posArg1 by the font's line-height byte
@ (gTextRenderState[0x11]) after each call. Stops once that out-param's
@ first byte reads 0 (string exhausted).
	thumb_func_start PrintTextBox
PrintTextBox: @ 0x08020FF8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r5, r0, #0     @ r5 = arg0 for the first call; DrawTextLine's return value after that
	adds r7, r1, #0     @ r7 = maxWidth (same every call)
	adds r4, r2, #0     @ r4 = posArg1 (incremented per line below)
	adds r6, r3, #0     @ r6 = posArg2 (unchanged)
	ldr r0, _0802100C @ =0x7FFFFFFF
	str r0, [sp, #0xc]   @ dummy first-iteration line-width accumulator
	b _08021030
	.align 2, 0
_0802100C: .4byte 0x7FFFFFFF
_08021010:
	add r0, sp, #0x24    @ out-param: where the next line should resume from
	str r0, [sp]
	ldr r0, [sp, #0x28]  @ pass through PrintTextBox's own stack-passed arg
	str r0, [sp, #4]
	add r0, sp, #0xc     @ out-param: this line's rendered width
	str r0, [sp, #8]
	adds r0, r5, #0
	adds r1, r7, #0
	adds r2, r4, #0
	adds r3, r6, #0
	bl DrawTextLine
	adds r5, r0, #0     @ r5 = this call's return value (becomes the next call's arg0)
	ldr r0, _08021044 @ =gTextRenderState
	ldrb r0, [r0, #0x11] @ line height
	adds r4, r4, r0      @ posArg1 += line height
_08021030:
	ldr r0, [sp, #0x24]
	ldrb r0, [r0]        @ first byte at the resume-from location -- 0 once exhausted
	cmp r0, #0
	bne _08021010
	adds r0, r5, #0
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08021044: .4byte gTextRenderState
	thumb_func_end PrintTextBox
