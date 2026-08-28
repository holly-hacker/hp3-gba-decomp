.text

@ Hand-written ARM-mode unsigned divide: quotient in r0, remainder in
@ r1. A 32-way binary-search dispatch on the dividend's bit length into
@ unrolled restoring division. Not compiler runtime -- libgcc's are the
@ Thumb routines in this directory.
	arm_func_start DivideUnsignedWorker
DivideUnsignedWorker: @ 0x080002E0
	cmp r1, #1
	beq _080005A4
	mov r2, #0
	cmp r1, r0, lsr #15
	bhi _0800038C
	cmp r1, r0, lsr #23
	bhi _08000344
	cmp r1, r0, lsr #27
	bhi _08000324
	cmp r1, r0, lsr #29
	bhi _08000318
	cmp r1, r0, lsr #30
	bhi _08000430
	b _08000424
_08000318:
	cmp r1, r0, lsr #28
	bhi _08000448
	b _0800043C
_08000324:
	cmp r1, r0, lsr #25
	bhi _08000338
	cmp r1, r0, lsr #26
	bhi _08000460
	b _08000454
_08000338:
	cmp r1, r0, lsr #24
	bhi _08000478
	b _0800046C
_08000344:
	cmp r1, r0, lsr #19
	bhi _0800036C
	cmp r1, r0, lsr #21
	bhi _08000360
	cmp r1, r0, lsr #22
	bhi _08000490
	b _08000484
_08000360:
	cmp r1, r0, lsr #20
	bhi _080004A8
	b _0800049C
_0800036C:
	cmp r1, r0, lsr #17
	bhi _08000380
	cmp r1, r0, lsr #18
	bhi _080004C0
	b _080004B4
_08000380:
	cmp r1, r0, lsr #16
	bhi _080004D8
	b _080004CC
_0800038C:
	cmp r1, r0, lsr #7
	bhi _080003DC
	cmp r1, r0, lsr #11
	bhi _080003BC
	cmp r1, r0, lsr #13
	bhi _080003B0
	cmp r1, r0, lsr #14
	bhi _080004F0
	b _080004E4
_080003B0:
	cmp r1, r0, lsr #12
	bhi _08000508
	b _080004FC
_080003BC:
	cmp r1, r0, lsr #9
	bhi _080003D0
	cmp r1, r0, lsr #10
	bhi _08000520
	b _08000514
_080003D0:
	cmp r1, r0, lsr #8
	bhi _08000538
	b _0800052C
_080003DC:
	cmp r1, r0, lsr #3
	bhi _08000404
	cmp r1, r0, lsr #5
	bhi _080003F8
	cmp r1, r0, lsr #6
	bhi _08000550
	b _08000544
_080003F8:
	cmp r1, r0, lsr #4
	bhi _08000568
	b _0800055C
_08000404:
	cmp r1, r0, lsr #1
	bhi _08000418
	cmp r1, r0, lsr #2
	bhi _08000580
	b _08000574
_08000418:
	cmp r1, r0
	bhi _08000598
	b _0800058C
_08000424:
	cmp r0, r1, lsl #30
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #30
_08000430:
	cmp r0, r1, lsl #29
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #29
_0800043C:
	cmp r0, r1, lsl #28
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #28
_08000448:
	cmp r0, r1, lsl #27
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #27
_08000454:
	cmp r0, r1, lsl #26
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #26
_08000460:
	cmp r0, r1, lsl #25
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #25
_0800046C:
	cmp r0, r1, lsl #24
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #24
_08000478:
	cmp r0, r1, lsl #23
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #23
_08000484:
	cmp r0, r1, lsl #22
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #22
_08000490:
	cmp r0, r1, lsl #21
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #21
_0800049C:
	cmp r0, r1, lsl #20
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #20
_080004A8:
	cmp r0, r1, lsl #19
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #19
_080004B4:
	cmp r0, r1, lsl #18
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #18
_080004C0:
	cmp r0, r1, lsl #17
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #17
_080004CC:
	cmp r0, r1, lsl #16
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #16
_080004D8:
	cmp r0, r1, lsl #15
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #15
_080004E4:
	cmp r0, r1, lsl #14
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #14
_080004F0:
	cmp r0, r1, lsl #13
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #13
_080004FC:
	cmp r0, r1, lsl #12
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #12
_08000508:
	cmp r0, r1, lsl #11
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #11
_08000514:
	cmp r0, r1, lsl #10
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #10
_08000520:
	cmp r0, r1, lsl #9
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #9
_0800052C:
	cmp r0, r1, lsl #8
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #8
_08000538:
	cmp r0, r1, lsl #7
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #7
_08000544:
	cmp r0, r1, lsl #6
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #6
_08000550:
	cmp r0, r1, lsl #5
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #5
_0800055C:
	cmp r0, r1, lsl #4
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #4
_08000568:
	cmp r0, r1, lsl #3
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #3
_08000574:
	cmp r0, r1, lsl #2
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #2
_08000580:
	cmp r0, r1, lsl #1
	adc r2, r2, r2
	subhs r0, r0, r1, lsl #1
_0800058C:
	cmp r0, r1
	adc r2, r2, r2
	subhs r0, r0, r1
_08000598:
	mov r1, r0
	mov r0, r2
	bx lr
_080005A4:
	mov r1, #0
	bx lr
	arm_func_end DivideUnsignedWorker
