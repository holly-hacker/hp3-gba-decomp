.text

@ Token-based LZSS-shaped decompressor. r0: compressed source. r1: dest.
@ r2: pointer to receive the decompressed byte count.
@
@ Each token starts with one control byte (ip):
@   1xxxxxxx  match / extended fill  (.Lmatch_or_fill, bit 0x80)
@   01xxxxxx  short byte-fill (RLE)  (.Lcheck_fill, bit 0x40)
@   00xxxxxx  literal copy           (.Lliteral_token)
@ Control byte 0 ends the stream.
@
@ All writes go through `strh`, even for odd-length tokens on unaligned
@ data: r5 is a 0/1 "byte pending" flag, r4 the pending low byte while
@ r5==1. Every token's tail flushes or re-arms this pair, hence each
@ copy/fill/literal case below has a fast (aligned) and slow (repacking)
@ loop. r7 is the destination start, for the final size = r0-r7.
	arm_func_start DecompressLzRle
DecompressLzRle:              @ 0x08006108
	push {r4, r5, r6, r7, r8, lr}
	mov r6, r0                @ r6 = source cursor, r0 = destination cursor
	mov r0, r1
	mov r5, #0
	mov r8, r2                @ r8 = out-size pointer
	ldrb ip, [r6], #1
	mov r7, r0
	cmp ip, r5
	beq .Lstream_end
.Lmatch_or_fill:              @ 0x0800612C
	tst ip, #0x80
	beq .Lcheck_fill

	@ match / extended-fill token (bit7 set), 2 bytes: byte0=ip (low 7
	@ bits), byte1 read below.
	@ distance = (byte0<<3) | (byte1>>5)
	@ length   = (byte1 & 0x1f) + 2   (2..33), unless that field is 0, in
	@   which case this is a long byte-fill run of length distance+0x42
	@   (66..1089) instead -- "distance" becomes extra length bits.
	and r3, ip, #0x7f
	ldrb ip, [r6], #1
	and r2, ip, #0x1f
	add r1, r2, #2
	cmp r1, #2                @ Z set iff the 5-bit length field was 0
	lsr r2, ip, #5
	orr r2, r2, r3, lsl #3    @ r2 = 10-bit distance
	addeq r1, r2, #0x42
	beq .Lfill_body

	@ genuine back-reference: copy r1 bytes from (dst + pending - distance)
	add r3, r0, r5
	rsb r3, r2, r3
	tst r3, #1
	beq .Lmatch_copy
	ldrb lr, [r3], #1
	eors r5, r5, #1
	movne r4, lr
	orreq r4, r4, lr, lsl #8
	strheq r4, [r0], #2
	sub r1, r1, #1
.Lmatch_copy:                 @ 0x08006180
	lsr ip, r1, #1
	cmp r5, #0
	bne .Lmatch_copy_unaligned
	cmp ip, #0
	and r2, r1, #1
	beq .Lmatch_copy_aligned_tail
.Lmatch_copy_aligned_loop:    @ 0x08006198
	ldrh r1, [r3], #2
	strh r1, [r0], #2
	subs ip, ip, #1
	bne .Lmatch_copy_aligned_loop
.Lmatch_copy_aligned_tail:    @ 0x080061A8
	cmp r2, #0
	ldrbne r4, [r3]
	movne r5, #1
	b .Lnext_control_byte
.Lmatch_copy_unaligned:       @ 0x080061B8
	cmp ip, #0
	and r2, r1, #1
	beq .Lmatch_copy_unaligned_tail
.Lmatch_copy_unaligned_loop:  @ 0x080061C4
	ldrh lr, [r3], #2
	orr r4, r4, lr, lsl #8
	strh r4, [r0], #2
	subs ip, ip, #1
	lsr r4, lr, #8
	bne .Lmatch_copy_unaligned_loop
.Lmatch_copy_unaligned_tail:  @ 0x080061DC
	cmp r2, #0
	ldrbne r3, [r3]
	orrne r4, r4, r3, lsl #8
	strhne r4, [r0], #2
	movne r5, #0
	b .Lnext_control_byte

.Lcheck_fill:                 @ 0x080061F4
	tst ip, #0x40
	beq .Lliteral_token
	and r3, ip, #0x3f
	add r1, r3, #3            @ short byte-fill: length = (ip & 0x3f) + 3
.Lfill_body:                  @ 0x08006204  @ shared with the extended-fill case above
	ldrb ip, [r6], #1         @ one fill byte, replicated as repeated "byte,byte" halfwords
	cmp r5, #0
	orrne r4, r4, ip, lsl #8
	subne r1, r1, #1
	strhne r4, [r0], #2
	orr r4, ip, ip, lsl #8
	lsrs ip, r1, #1
	and r2, r1, #1
	beq .Lfill_tail
.Lfill_loop:                  @ 0x08006228
	strh r4, [r0], #2
	subs ip, ip, #1
	bne .Lfill_loop
.Lfill_tail:                  @ 0x08006234
	mov r5, r2
	and r3, r4, #0xff
	cmp r5, #0
	movne r4, r3
	b .Lnext_control_byte

.Lliteral_token:              @ 0x08006248  @ literal-copy: ip itself is the byte count (0..63)
	mov r1, ip
	tst r6, #1
	beq .Lliteral_aligned
	eors r5, r5, #1
	ldrbne r4, [r6], #1
	ldrbeq r3, [r6], #1
	orreq r4, r4, r3, lsl #8
	strheq r4, [r0], #2
	sub r1, r1, #1
.Lliteral_aligned:            @ 0x0800626C
	lsr ip, r1, #1
	cmp r5, #0
	bne .Lliteral_unaligned
	cmp ip, #0
	and r2, r1, #1
	beq .Lliteral_aligned_tail
.Lliteral_aligned_loop:       @ 0x08006284
	ldrh r3, [r6], #2
	strh r3, [r0], #2
	subs ip, ip, #1
	bne .Lliteral_aligned_loop
.Lliteral_aligned_tail:       @ 0x08006294
	cmp r2, #0
	ldrbne r4, [r6], #1
	movne r5, #1
	b .Lnext_control_byte
.Lliteral_unaligned:          @ 0x080062A4
	cmp ip, #0
	and r2, r1, #1
	beq .Lliteral_unaligned_tail
.Lliteral_unaligned_loop:     @ 0x080062B0
	ldrh lr, [r6], #2
	orr r4, r4, lr, lsl #8
	strh r4, [r0], #2
	subs ip, ip, #1
	lsr r4, lr, #8
	bne .Lliteral_unaligned_loop
.Lliteral_unaligned_tail:     @ 0x080062C8
	cmp r2, #0
	ldrbne r3, [r6], #1
	movne r5, #0
	orrne r4, r4, r3, lsl #8
	strhne r4, [r0], #2

.Lnext_control_byte:          @ 0x080062DC
	ldrb ip, [r6], #1
	cmp ip, #0
	bne .Lmatch_or_fill
.Lstream_end:                 @ 0x080062E8
	cmp r5, #0
	strbne r4, [r0], #1       @ flush a final odd pending byte
	rsb r3, r7, r0
	str r3, [r8]
	pop {r4, r5, r6, r7, r8, lr}
	bx lr
	arm_func_end DecompressLzRle
