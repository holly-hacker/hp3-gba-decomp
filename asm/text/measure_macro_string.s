.text

@ MeasureMacroString(str) -> total pixel width.
@ Sums GetGlyphWidth() over every glyph code in str, recursing into
@ MeasureMacroString itself for nested 0x40-prefixed macro codes (via
@ sTextMacroTable) exactly like DrawTextLine's own inline glyph loop --
@ this is the same measuring logic factored out for reuse by
@ sub_080208B4 (the actual glyph-blit routine DrawTextLine hands off
@ to once a line is finalized). Measures only -- it draws nothing
@ itself, despite being called from inside the drawing path.
	thumb_func_start MeasureMacroString
MeasureMacroString: @ 0x08020E40
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	movs r5, #0
	ldrb r0, [r4]
	cmp r0, #0
	beq _MeasureMacroString_L3
	ldr r7, _MeasureMacroString_L1 @ =sTextMacroTable
	ldr r6, _MeasureMacroString_L2 @ =gTextRenderState
_MeasureMacroString_L4:
	cmp r0, #0x40
	bne _MeasureMacroString_L5
	adds r4, #1
	ldrb r0, [r4]
	subs r0, #0x31
	lsls r0, r0, #2
	adds r0, r0, r7
	ldr r0, [r0]
	bl MeasureMacroString
	b _MeasureMacroString_L6
	.align 2, 0
_MeasureMacroString_L1: .4byte sTextMacroTable
_MeasureMacroString_L2: .4byte gTextRenderState
_MeasureMacroString_L5:
	ldrb r1, [r4]
	cmp r1, #0xef
	bls _MeasureMacroString_L7
	lsls r1, r1, #8
	adds r4, #1
	ldrb r0, [r4]
	orrs r1, r0
	ldr r0, [r6, #4]
	b _MeasureMacroString_L8
_MeasureMacroString_L7:
	ldr r0, [r6]
_MeasureMacroString_L8:
	bl GetGlyphWidth
_MeasureMacroString_L6:
	adds r5, r5, r0
	adds r4, #1
	ldrb r0, [r4]
	cmp r0, #0
	bne _MeasureMacroString_L4
_MeasureMacroString_L3:
	adds r0, r5, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
	thumb_func_end MeasureMacroString
