.text

@ Interrupt dispatcher installed at gIntrVectorPtr. Reads IE & IF, picks the
@ highest-priority pending source, acknowledges it, and calls the matching
@ gIntrTable slot in system mode. Bit 0x20 (timer 2) first saves the caller's
@ [sp, #0x14] to 0x030015A0. Bit 0x2000 (Game Pak) writes 0 to SOUNDCNT_X
@ (0x04000084) and hangs.
	arm_func_start IntrMain
IntrMain: @ 0x08000134
	mov r3, #0x4000000
	add r3, r3, #0x200
	ldr r2, [r3]
	tst r2, #0x20
	ldrne r0, _0800026C @ =g_pTimer2DebugPc
	ldrne r1, [sp, #0x14]
	strne r1, [r0]
	ldrh r1, [r3, #8]
	mrs r0, spsr
	push {r0, r1, r2, r3, lr}
	mov r0, #1
	strh r0, [r3, #8]
	and r1, r2, r2, lsr #16
	ldr ip, _08000270 @ =gIntrTable
	ands r0, r1, #0xc0
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #1
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #4
	bne _08000208
	add ip, ip, #4
	ands r0, r1, #0x10
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #2
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #8
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x20
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x100
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x200
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x400
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x800
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x1000
	bne _08000210
	add ip, ip, #4
	ands r0, r1, #0x2000
	strbne r0, [r3, #-0x17c]
_08000204:
	bne _08000204
_08000208:
	ldr r1, _08000274 @ =0x00002034
	b _08000214
_08000210:
	ldr r1, _08000278 @ =0x000020F4
_08000214:
	strh r0, [r3, #2]
	bic r2, r2, r0
	and r1, r1, r2
	strh r1, [r3]
	mrs r3, apsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x1f
	msr cpsr_fc, r3
	ldr r0, [ip]
	stmdb sp!, {lr}
	add lr, pc, #0x0 @ =_08000244
	bx r0
_08000244:
	@ handler return point, reached through lr rather than a branch
	ldm sp!, {lr}
	mrs r3, cpsr
	bic r3, r3, #0xdf
	orr r3, r3, #0x92
	msr cpsr_fc, r3
	ldm sp!, {r0, r1, r2, r3, lr}
	strh r2, [r3]
	strh r1, [r3, #8]
	msr spsr_fc, r0
	bx lr
_0800026C: .4byte g_pTimer2DebugPc
_08000270: .4byte gIntrTable
_08000274: .4byte 0x00002034
_08000278: .4byte 0x000020F4
	arm_func_end IntrMain
