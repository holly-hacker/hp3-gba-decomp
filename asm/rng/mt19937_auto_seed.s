.text

	thumb_func_start Mt19937AutoSeed
Mt19937AutoSeed: @ us:0x0803B330, jp:0x0803B398
	push {r4, r5, r6, lr}
	ldr r0, _Mt19937AutoSeed_L1 @ =gMt19937RemainingIndices
	movs r1, #1
	rsbs r1, r1, #0
	str r1, [r0]
	ldr r0, _Mt19937AutoSeed_L2 @ =gMt19937RemainingIndices2
	str r1, [r0]
	ldr r4, _Mt19937AutoSeed_L3 @ =gMt19937SeedValue
	ldr r5, _Mt19937AutoSeed_L4 @ =gMt19937SeedSourceStruct
	ldr r0, [r5]
	ldr r1, [r0, #0x1c]
	lsls r1, r1, #4
	ldr r6, _Mt19937AutoSeed_L5 @ =gMt19937SeedSourceCounter
	ldrh r0, [r6]
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r0, [r4]
	adds r0, r0, r1
	str r0, [r4]
	cmp r0, #0
	bne _Mt19937AutoSeed_L10
	bl Mt19937Next
	ldr r1, _Mt19937AutoSeed_L6 @ =0x000FFF1F
	bl umodsi3
	adds r0, #1
	str r0, [r4]
_Mt19937AutoSeed_L10:
	ldr r0, _Mt19937AutoSeed_L7 @ =gMt19937AutoSeedCallCount
	ldr r2, [r0]
	adds r2, #1
	str r2, [r0]
	ldr r0, [r4]
	lsls r0, r0, #8
	ldr r1, [r5]
	ldr r1, [r1, #0x1c]
	lsls r1, r1, #6
	adds r0, r0, r1
	lsls r2, r2, #4
	adds r0, r0, r2
	ldrh r1, [r6]
	orrs r0, r1
	str r0, [r4]
	bl Mt19937SeedArray
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_Mt19937AutoSeed_L1: .4byte gMt19937RemainingIndices
_Mt19937AutoSeed_L2: .4byte gMt19937RemainingIndices2
_Mt19937AutoSeed_L3: .4byte gMt19937SeedValue
_Mt19937AutoSeed_L4: .4byte gMt19937SeedSourceStruct
_Mt19937AutoSeed_L5: .4byte gMt19937SeedSourceCounter
_Mt19937AutoSeed_L6: .4byte 0x000FFF1F
_Mt19937AutoSeed_L7: .4byte gMt19937AutoSeedCallCount
	thumb_func_end Mt19937AutoSeed
