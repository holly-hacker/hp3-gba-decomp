.text

@ LZ77-style decompressor with a small header-supplied length table and a
@ capped-unary/raw-bits ("Elias-gamma-shaped") code for lengths and
@ distances -- not the real BIOS Huffman codec (that's dispatch type 2,
@ a plain `svc 0x13`); this is a proprietary scheme. r0: compressed
@ source. r1: destination. r2: pointer to receive the decompressed byte
@ count (may be NULL; checked at the very end).
@
@ Codec header (4 bytes, right after the outer dispatcher header, see
@ docs/formats/graphics.md): byte0 = size of a small length table copied
@ onto the stack (indexed `table[code-1]` for short run-length codes);
@ byte1 = match sentinel (r4, see the dispatch loop); byte2 = bit-width
@ of an extra distance-extension field; byte3 = bit-width of a literal
@ byte's high part (low part is the complementary 8-byte3 bits), also
@ reused as a raw field width elsewhere. r2 packs
@ byte3:byte2:(8-byte3) into bits[23:16]:[15:8]:[7:0] once, so callers
@ pull either width out with a plain mask/shift.
	arm_func_start DecompressGammaLz
DecompressGammaLz:                     @ 0x080005EC
	push {r1, r2, r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
	sub sp, sp, #0x24                @ scratch: sp+0 unused pad, sp+4.. holds the copied length table
	ldr fp, [r0], #4                 @ fp = codec header word (LE byte0..3)
	mov r5, #0xff
	and r3, r5, fp                   @ r3 = byte0 = length-table byte count
	and r4, r5, fp, lsr #8           @ r4 = byte1 = match sentinel
	lsr r2, fp, #0x10                @ r2 = byte2 | byte3<<8
	lsr r5, r2, #8                   @ r5 = byte3
	rsb r5, r5, #8                   @ r5 = 8 - byte3
	add r2, r5, r2, lsl #8           @ r2 = byte3:byte2:(8-byte3) packed
	add r5, sp, #4                   @ r5 = length-table destination
.Ltable_copy_loop:                   @ 0x08000618
	ldr fp, [r0], #4
	str fp, [r5], #4
	subs r3, r3, #4
	bne .Ltable_copy_loop
	mov r8, #-0x80000000             @ bit-buffer sentinel: top bit set forces a refill on the first GetBit
	mov ip, #0                       @ ip = output halfword-pack parity flag, like DecompressLzRle's r5
	b .Ldispatch

@ --- bitstream primitives (all operate on r8 = 32-bit MSB-first shift
@ register, refilled a word at a time from [r0] when it runs dry) ---

@ GetGammaCode: capped-unary prefix (up to 7 leading 1-bits, via GetBit)
@ followed by that many raw bits appended via AppendBits; returns in r5
@ a value in [1, 255] (1 if the very first bit was 0). This is the
@ length/distance/literal-selector code read at the top of most tokens.
	arm_func_start GetGammaCode
GetGammaCode:                        @ 0x08000634
	mov r5, #1
	mov sb, r5                       @ sb counts consumed 1-bits, +1 (bias)
	adds r8, r8, r8                  @ GetBit, inlined and unrolled x4 below x2
	ldreq r8, [r0], #4
	adcseq r8, r8, r8
	blo .Lbits_done                  @ bit was 0: stop counting, no extra bits to append
	add sb, sb, #1
.Lunary_loop:                        @ 0x08000650
	adds r8, r8, r8
	ldreq r8, [r0], #4
	adcseq r8, r8, r8
	blo .Lbits_done
	add sb, sb, #1
	adds r8, r8, r8
	ldreq r8, [r0], #4
	adcseq r8, r8, r8
	blo .Lbits_done
	add sb, sb, #1
	adds r8, r8, r8
	ldreq r8, [r0], #4
	adcseq r8, r8, r8
	blo .Lbits_done
	add sb, sb, #1
	cmp sb, #8                       @ capped at 7 one-bits (sb reaches 8)
	bne .Lunary_loop
	subs sb, sb, #1                  @ sb = number of 1-bits actually seen
	bne .Lappend_bits                @ >0: append that many raw bits onto r5 (=1) via AppendBits
	bx lr                            @ ==0 (first bit was 0): r5 stays 1, done
	arm_func_end GetGammaCode

@ GetBit: single raw bit, left in the carry flag for the caller's own
@ conditional branch.
	arm_func_start GetBit
GetBit:                              @ 0x080006A0
	ldr r8, [r0], #4                 @ reached only mid-refill, via the caller's own inlined
	adcseq r8, r8, r8                @ `adds r8,r8,r8` -- completes that refill+shift
	bx lr
@ AppendBits(sb): r5 = (r5 << sb) | next `sb` raw bits -- extends an
@ existing accumulator.
.Lappend_bits:                       @ 0x080006AC
	lsls r3, r8, sb
	beq .Lbits_loop                  @ fewer than `sb` bits buffered: slow one-bit-at-a-time fallback
	rsb r3, sb, #0x20
	lsr r3, r8, r3
	orr r5, r3, r5, lsl sb
	lsl r8, r8, sb
	bx lr
	arm_func_end GetBit

@ ReadBits(sb): r5 = next `sb` raw bits, fresh (previous r5 discarded).
	arm_func_start ReadBits
ReadBits:                            @ 0x080006C8
	lsls r5, r8, sb
	beq .Lbits_loop                  @ fewer than `sb` bits buffered: slow one-bit-at-a-time fallback
	rsb r5, sb, #0x20
	lsr r5, r8, r5
	lsl r8, r8, sb
	bx lr
	arm_func_end ReadBits

@ Slow one-bit-at-a-time tail, shared by GetGammaCode's suffix bits and
@ the AppendBits/ReadBits fallback above; also reachable via the fixed
@ sb=8 entry below for a raw literal-byte read.
	arm_func_start ReadByteSlow
ReadByteSlow:                        @ 0x080006E0
	mov sb, #8
.Lbits_loop:                         @ 0x080006E4
	adds r8, r8, r8
	ldreq r8, [r0], #4
	adcseq r8, r8, r8
	adc r5, r5, r5
.Lbits_done:                         @ 0x080006F4
	subs sb, sb, #1
	bne .Lbits_loop
	bx lr
	arm_func_end ReadByteSlow

@ --- main token loop ---
@
@ Each iteration reads a `byte3`-bit prefix into r5 and compares it to
@ the sentinel r4. No match: the remaining (8-byte3) bits complete an
@ 8-bit literal, emitted at .Lemit_literal. Match: a gamma code picks
@ one of three token kinds --
@   code >= 2                       -> back-reference (.Lmatch_extended)
@   code == 1, lookahead bits "00"  -> back-reference, fixed length 2
@   code == 1, lookahead bits "01"  -> literal via sentinel swap
@                                       (.Lliteral_via_swap: r4/r5 swap,
@                                       so r4 becomes 0 for the rest of
@                                       the stream -- the sentinel is
@                                       stateful, not a fixed constant)
@   code == 1, lookahead bit  "1"   -> byte-fill run (.Ldecode_run)
@
@ All emitted bytes go out via `strh` in pairs, packed through `ip`
@ (0/1 parity) and `sl` (pending halfword) -- same mechanism as
@ DecompressLzRle's parity pair, different register assignment.
.Lliteral_via_swap:                  @ 0x08000700
	lsrs sb, r2, #0x10
	blne ReadBits
	mov fp, r4                       @ SWAP(r4, r5)
	mov r4, r5
	mov r5, fp
.Lemit_literal:                      @ 0x08000714  @ literal emission (also the top-level "not a match" path)
	ands sb, r2, #0xff
	blne .Lappend_bits               @ append the low (8-byte3) bits to complete the literal byte
	eors ip, ip, #1
	movne sl, r5                     @ odd byte: buffer as pending low byte
	addeq sl, sl, r5, lsl #8         @ even byte: completes the pending halfword
	strheq sl, [r1], #2
.Ldispatch:                          @ 0x0800072C  @ top-level dispatch / loop continuation
	mov r5, #0
	mov fp, #0
	lsrs sb, r2, #0x10
	blne ReadBits                    @ r5 = literal-byte high part / sentinel probe
	cmp r5, r4
	bne .Lemit_literal               @ no match: r5 already holds most of a literal byte
	bl GetGammaCode                  @ match: read the token-selector code
	mov r6, r5                       @ r6 = match length (code>=2 case)
	lsrs r5, r5, #1
	bne .Lmatch_extended             @ code >= 2: extended-length back-reference
	adds r8, r8, r8                  @ code == 1: 2-bit lookahead
	bleq GetBit
	blo .Lmatch_copy                 @ "00": fixed length-2 back-reference (fp already 0)
	adds r8, r8, r8
	bleq GetBit
	blo .Lliteral_via_swap           @ "01": literal via sentinel-swap
	bl GetGammaCode                  @ "1": run-length byte-fill token
	mov r6, r5                       @ r6 = run-length code
	cmp r5, #0x80
	blo .Ldecode_run                 @ short run: skip the extra length byte
	adds r8, r8, r8                  @ long run: 1 extra bit + a whole extra
	bleq GetBit                      @ gamma code, to build a wider count
	adc r6, r5, r5
	and r6, r6, #0xff
	bl GetGammaCode
	sub fp, r5, #1
.Ldecode_run:                        @ 0x08000794
	bl GetGammaCode                  @ read the fill-byte code
	cmp r5, #0x20
	addlo r5, r5, #3                 @ code < 0x20: table[code-1] (table starts at sp+4)
	ldrblo r5, [sp, r5]
	movhs sb, #3                     @ code >= 0x20: extend with 3 more raw bits instead
	blhs .Lappend_bits
	and r5, r5, #0xff                @ r5 = the fill byte
	add r6, r6, #1                   @ r6 = run length: low byte + 1, high byte from fp
	add r6, r6, fp, lsl #8
.Lemit_run:                          @ 0x080007B8  @ emit `r6` halfword-pairs of fill byte `r5`
	tst ip, #1
	addne sl, sl, r5, lsl #8
	strhne sl, [r1], #2
	subne r6, r6, #1
	add sl, r5, r5, lsl #8
.Lemit_run_pack:                     @ 0x080007CC
	and r5, r6, #1
	lsrs r6, r6, #1
.Lemit_run_loop:                     @ 0x080007D4
	strhne sl, [r1], #2
	subs r6, r6, #1
	bgt .Lemit_run_loop
	movs ip, r5
	andne sl, sl, #0xff
	b .Ldispatch

.Lmatch_extended:                    @ 0x080007EC  @ code >= 2: extended-length back-reference
	bl GetGammaCode                  @ read the length code proper
	cmp r5, #0xff
	beq .Lstream_end                 @ length code 0xff: end-of-stream sentinel
	sub fp, r5, #1                   @ fp = length-1 (low part of the distance built below)
	lsr sb, r2, #8
	ands sb, sb, #0xff               @ sb = byte2 (extra distance-field width)
	beq .Lmatch_copy                 @ width 0: distance is fp alone
	lsl fp, fp, sb
	bl ReadBits                      @ else fold in `byte2` extra raw bits (fresh)
	orr fp, fp, r5
.Lmatch_copy:                        @ 0x08000814  @ shared back-reference copy (fp = distance high part, 0 for length-2)
	lsls r5, r8, #8
	lsrne r5, r8, #0x18
	lslne r8, r8, #8
	bleq ReadByteSlow                @ r5 = a raw distance byte
	add fp, r5, fp, lsl #8           @ fp = full distance
	sub r7, r1, fp                   @ r7 = copy-source = dst - distance - 1 + pending-parity offset
	sub r7, r7, #1
	add r7, r7, ip
	add r6, r6, #1                   @ r6 = match length (code + 1)
	sub r5, r1, r7                   @ r5 = "gap" between write cursor and copy source
	cmp r5, #1
	bgt .Lmatch_copy_bulk            @ gap > 1: safe to bulk-copy
	bne .Lmatch_copy_gap0            @ gap == 0: fully self-overlapping (byte-repeat)
	ldrb r5, [r7], #1                @ gap == 1: peel one byte, then join the run emitter
	tst ip, #1
	beq .Lemit_run
	add sl, sl, r5, lsl #8
	strh sl, [r1], #2
	sub r6, r6, #1
	b .Lemit_run_pack
.Lmatch_copy_gap0:                   @ 0x08000864  @ gap 0: source==dest, must copy byte-by-byte so each write is visible
	tst ip, #1
	ldrbeq r5, [r7], #1
	andne r5, sl, #0xff
	b .Lemit_run
.Lmatch_copy_bulk:                   @ 0x08000874  @ gap > 1: bulk-copy from far enough behind the write cursor
	tst r7, #1
	beq .Lmatch_copy_halfwords
	ldrb r5, [r7], #1                @ peel one byte first if the copy source is halfword-misaligned
	eors ip, ip, #1
	movne sl, r5
	addeq sl, sl, r5, lsl #8
	strheq sl, [r1], #2
	subs r6, r6, #1
.Lmatch_copy_halfwords:              @ 0x08000894
	lsrs fp, r6, #1                  @ fp = whole halfwords left to copy
	beq .Lmatch_copy_tail_odd
	tst ip, #1
	bne .Lmatch_copy_unaligned_loop  @ pending byte set: repack every source halfword
.Lmatch_copy_aligned_loop:           @ 0x080008A4  @ fast path: aligned halfword-for-halfword copy
	ldrh r5, [r7], #2
	strh r5, [r1], #2
	subs fp, fp, #1
	bne .Lmatch_copy_aligned_loop
	b .Lmatch_copy_tail
.Lmatch_copy_unaligned_loop:         @ 0x080008B8  @ slow path: repack every source halfword into the pending offset
	ldrh r5, [r7], #2
	add r5, sl, r5, lsl #8
	strh r5, [r1], #2
	lsr sl, r5, #0x10
	subs fp, fp, #1
	bne .Lmatch_copy_unaligned_loop
	mov ip, #1
.Lmatch_copy_tail:                   @ 0x080008D4
	tst r6, #1
	beq .Ldispatch                   @ even total length: nothing left over
.Lmatch_copy_tail_odd:               @ 0x080008DC
	ldrb r5, [r7], #1                @ odd total length: one trailing byte
	eors ip, ip, #1
	movne sl, r5
	addeq sl, sl, r5, lsl #8
	strheq sl, [r1], #2
	b .Ldispatch

.Lstream_end:                        @ 0x080008F4  @ end of stream (length code 0xff)
	tst ip, #1
	strbne sl, [r1], #1              @ flush a final odd pending byte
	add sp, sp, #0x24
	pop {r0, r2, r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
	cmp r2, #0
	bxeq lr                          @ out-size pointer is NULL: skip writing the count
	subs r1, r1, r0                  @ decompressed size = dst cursor - dst start (r0 is the original r1)
	str r1, [r2]
	bx lr
	arm_func_end DecompressGammaLz
