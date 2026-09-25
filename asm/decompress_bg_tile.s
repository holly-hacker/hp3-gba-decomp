.text

@ Canonical-Huffman bit-stream decoder for one BG tile. r0: bit offset
@ into the ROM (LSB-first, bit 0 = 0x08000000). r1: dest.
@ r2: output size in bytes. r3: code table. Copied into IWRAM by
@ InstallBgTileCodec, called via bx.
@
@ Table: u8 count[18] (+0x00, codes per bit length), u8 base[18] (+0x12,
@ first symbol index per length), u8 symbol[] (+0x24).
@ Per symbol, bits are shifted into `code` until code < count[len], else
@ code -= count[len]. Symbol = symbol[base[len] + code]. Symbol pairs form
@ halfwords (first = low byte); r6 == 0x100 means no low byte pending.
	arm_func_start DecompressBgTile
DecompressBgTile:            @ 0x08006300
	push {r4, r5, r6, r7, r8, sl, lr}
	mov sl, r1                @ sl = dest cursor
	mov r6, #0x100            @ no pending low byte
	asr r4, r2, #1            @ r4 = halfwords left
	and r2, r0, #0x1f         @ r2 = bit position within word
	rsb r1, r2, #0x1f         @ r1 = bits left in the buffered word - 1
	lsr r0, r0, #3
	bic r0, r0, #3            @ byte offset of the containing word
	add r5, r0, #0x8000000
	cmp r4, #0
	mov r0, r3                @ r0 = table (count[])
	add r8, r0, #0x24         @ r8 = symbol[]
	ldr lr, [r5], #4
	add r7, r0, #0x12         @ r7 = base[]
	lsr lr, lr, r2            @ drop the bits already consumed
	ble .Ldone
.Lnext_symbol:                @ 0x08006340
	mov ip, #0                @ ip = code length index
	mov r2, ip                @ r2 = code accumulated so far
.Lnext_bit:                   @ 0x08006348
	and r3, lr, #1
	orr r2, r3, r2, lsl #1    @ append next stream bit
	sub r1, r1, #1
	cmn r1, #1
	ldreq lr, [r5], #4        @ buffer empty: refill
	moveq r1, #0x1f
	lsrne lr, lr, #1
	ldrb r3, [r0, ip]         @ count[len]
	cmp r2, r3
	rsbge r2, r3, r2          @ code >= count: skip this length
	addge ip, ip, #1
	bge .Lnext_bit
	ldrb r3, [r7, ip]         @ base[len]
	add r3, r3, r2
	ldrb r3, [r8, r3]         @ r3 = decoded symbol
	cmp r6, #0x100
	beq .Lstash_low
	sub r4, r4, #1
	add r3, r6, r3, lsl #8    @ high byte + pending low byte
	strh r3, [sl], #2
	mov r6, #0x100
	b .Lcheck_count
.Lstash_low:                  @ 0x080063A0
	mov r6, r3
.Lcheck_count:                @ 0x080063A4
	cmp r4, #0
	bgt .Lnext_symbol
.Ldone:                       @ 0x080063AC
	pop {r4, r5, r6, r7, r8, sl, lr}
	bx lr
	arm_func_end DecompressBgTile
