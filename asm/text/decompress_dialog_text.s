.text

@ DecompressDialogText(stringId, outBuf, maxSize) -> 0 on success,
@ 1 if no language blob is installed (InitDialogTextTable never
@ called), 2 if the decoded string would overflow maxSize.
@
@ Decodes one string from the active language blob's Huffman-style
@ bitstream into outBuf. RAM globals (set up by InitDialogTextTable):
@   gDialogTextBlobBase    active blob's base pointer (0 = none installed)
@   gDialogTextOffsetTable pointer to the blob's u32[] offset table, one
@                          entry per string ID; offsetTable[stringId] is
@                          a byte offset from the blob base to that
@                          string's compressed bitstream
@   gDialogTextTreeNodes   pointer to the blob's Huffman tree node
@                          table: 4 bytes/node (u16 zero-bit child @+0,
@                          u16 one-bit child @+2); a child value <=0xFF
@                          is a decoded output byte (leaf), >0xFF is the
@                          next node's index (internal), at treeBase +
@                          (child-0x100)*4
@
@ Bits are read LSB-first out of each input byte, refilling one byte at
@ a time. Each decoded byte >0xEF starts a two-byte extended glyph code
@ (paired with the next decoded byte); decoding stops on a plain
@ (non-paired) decoded byte of 0 -- ordinary C-string termination, just
@ applied to glyph codes rather than raw bytes.
	thumb_func_start DecompressDialogText
DecompressDialogText: @ 0x08024DC8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	adds r4, r0, #0     @ r4 = stringId
	mov sb, r1           @ sb = outBuf
	str r2, [sp]          @ [sp] = maxSize
	movs r0, #0
	mov ip, r0           @ ip = "more to decode" / pending-extended-code payload
	mov r8, r0           @ r8 = pending-extended-code flag
	ldr r0, _08024DEC @ =gDialogTextBlobBase
	ldr r3, [r0]          @ r3 = active blob base
	cmp r3, #0
	bne _08024DF4
	movs r0, #1           @ no blob installed
	b _08024EA8
	.align 2, 0
_08024DEC: .4byte gDialogTextBlobBase
_08024DF0:
	movs r0, #2           @ overflow
	b _08024EA8
_08024DF4:
	ldr r0, _08024E2C @ =gDialogTextOffsetTable
	ldr r1, [r0]          @ r1 = offset table pointer
	lsls r0, r4, #2
	adds r0, r0, r1        @ r0 = &offsetTable[stringId]
	ldr r0, [r0]           @ r0 = offsetTable[stringId]
	adds r2, r3, r0        @ r2 = bitstream read cursor (byte pointer)
	movs r6, #0           @ r6 = output write index
	movs r4, #0           @ r4 = bit position within the current byte (0-7)
	ldrb r7, [r2]          @ r7 = current input byte
	adds r2, #1
	ldr r1, _08024E30 @ =0xFFFFFC00
	mov sl, r1           @ sl = -1024, folded into every tree-node address below
_08024E0C:                @ outer loop: decode one glyph-code byte
	movs r3, #0x80
	lsls r3, r3, #1       @ r3 = 0x100 = tree root node index
	adds r5, r6, #1       @ r5 = tentative next write index
_08024E12:                @ inner loop: walk the tree one bit at a time
	adds r0, r7, #0
	asrs r0, r4
	movs r1, #1
	ands r0, r1            @ r0 = next input bit (bit r4 of the current byte)
	cmp r0, #0
	beq _08024E38
	ldr r0, _08024E34 @ =gDialogTextTreeNodes
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	add r0, sl             @ r0 = &treeNodes[r3] (via the -1024 fold)
	ldrh r3, [r0, #2]      @ bit set: r3 = one-bit child
	b _08024E44
	.align 2, 0
_08024E2C: .4byte gDialogTextOffsetTable
_08024E30: .4byte 0xFFFFFC00
_08024E34: .4byte gDialogTextTreeNodes
_08024E38:
	ldr r0, _08024E74 @ =gDialogTextTreeNodes
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	add r0, sl
	ldrh r3, [r0]          @ bit clear: r3 = zero-bit child
_08024E44:
	adds r4, #1
	cmp r4, #8
	bne _08024E50
	movs r4, #0           @ used all 8 bits: refill the next input byte
	ldrb r7, [r2]
	adds r2, #1
_08024E50:
	cmp r3, #0xff
	bhi _08024E12          @ r3 > 0xff: still an internal node, keep walking
	mov r1, sb             @ r3 <= 0xff: it's a decoded glyph byte
	adds r0, r1, r6
	strb r3, [r0]           @ outBuf[writeIndex] = r3
	adds r6, r5, #0        @ writeIndex = tentative next index
	lsls r0, r3, #0x18
	lsrs r1, r0, #0x18      @ r1 = decoded byte value (redundant re-mask)
	cmp r1, #0xef
	bls _08024E78           @ <=0xef: a plain single-byte glyph
	mov r3, r8
	cmp r3, #0
	bne _08024E7E           @ >0xef and already pending: this completes a pair
	lsls r1, r1, #8         @ >0xef, first of a pair: stash it shifted up
	mov ip, r1
	movs r0, #1
	mov r8, r0              @ mark pending
	b _08024E8E
	.align 2, 0
_08024E74: .4byte gDialogTextTreeNodes
_08024E78:
	mov r3, r8
	cmp r3, #0
	beq _08024E8C           @ <=0xef and nothing pending: ordinary case
_08024E7E:                 @ pair-completion path (also reached for malformed
	lsrs r0, r0, #0x18      @ input: a <=0xef byte arriving while pending)
	mov r1, ip
	orrs r1, r0             @ merge with the stashed high byte
	mov ip, r1
	movs r3, #0
	mov r8, r3              @ clear pending
	b _08024E8E
_08024E8C:
	mov ip, r1              @ ip = this decoded byte's own value
_08024E8E:
	mov r1, sb
	adds r0, r6, r1
	subs r0, #1
	ldrb r0, [r0]           @ r0 = the byte just written
	cmp r0, #0
	beq _08024EA0           @ 0: possible terminator, skip the overflow check
	ldr r3, [sp]
	cmp r6, r3
	beq _08024DF0            @ non-zero and buffer now full: overflow
_08024EA0:
	mov r0, ip
	cmp r0, #0
	bne _08024E0C            @ ip != 0: more to decode (see the pair/ip logic above)
	movs r0, #0              @ ip == 0 only for a genuine plain 0 byte: success
_08024EA8:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	thumb_func_end DecompressDialogText
