/*
 * Krawall, XM/S3M Modplayer Library
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License in COPYING for more details.
 *
 * Modified to match the code in Harry Potter and the Prisoner of Azkaban
 * (Game Boy Advance); changes are marked HP3-GBA.
 */

#include "regs.h"
#include "directsound.h"

#if IWRAM_USAGE_SMALL || IWRAM_USAGE_MEDIUM
static s8 lBuffer[ DMABUFFERSIZE ] EWRAM __attribute__((__aligned__(4)));
static s8 rBuffer[ DMABUFFERSIZE ] EWRAM __attribute__((__aligned__(4)));
#else
static s8 lBuffer[ DMABUFFERSIZE ] IWRAM __attribute__((__aligned__(4)));
static s8 rBuffer[ DMABUFFERSIZE ] IWRAM __attribute__((__aligned__(4)));
#endif

static u32 nextSample EWRAM;
static u32 currMixBlock EWRAM;
static u32 lastDmaBlock EWRAM;	// HP3-GBA: added

static u32 active EWRAM;

volatile u32 dmaBlock EWRAM;	// HP3-GBA: upstream volatile u8, toggled by kradInterrupt
u8 dsStereo IWRAM;


// HP3-GBA: getDmaAddress() follows dsInit(); upstream has it here

void dsInit( u32 stereo )
{
	dsStereo = stereo;

    // soundchip on
	SGCNT1 = ( 1 << 7 );

	// output ratio full range A/B | output to L on A | FIFO A reset | output to R on B | FIFO B reset
	SGCNT0_H = ( ( 3 << 2 ) | ( 1 << 9 ) | ( 1 << 11 ) | ( 1 << 12 ) | ( 1 << 15 ) );

	if( !dsStereo ) { // mono
		SGCNT0_H |= ( 1 << 8 ); // output A to R as well
		SGCNT0_H &= 0x0fff;
	}

	// dma's source-address
	DM1SAD = ( u32 )&lBuffer;
	DM2SAD = ( u32 )&rBuffer;

	// dma's dest -> ds a/b fifo
	DM1DAD = ( u32 )&SGFIFOA;
	DM2DAD = ( u32 )&SGFIFOB;

	// dest fixed | dma repeat on | transfer-type 32b | dma-transfer timing 3 (direct sound)
	DM1CNT_H = ( 2 << 5 ) | ( 1 << 9 ) | ( 1 << 10 ) | ( 3 << 12 ) | ( 1 << 15 );

	if( dsStereo ) {
		DM2CNT_H = DM1CNT_H;
	}

	/*
	 this is a little tricky:
	 we must reset the dma after DMABUFFERSIZE samples have been played
	 (=# TM0 has overflowed)
	 now gba's fifo is a little weird, it fills it's fifo-buffer (32 bytes) quite fast,
	 actually it has already transfered 32 bytes (=2 transfers a 16 byte) when only
	 2 samples have been played.
	 when the 3rd dma-transfer is done (=48 bytes) only 16 samples have been played
	 so the dma is 32 bytes ahead.
	 therefore we must reset the DMA 32 bytes earlier, this is where the +32 comes from.
	 the -3 is a few samples we wait to reset the dma so we don't reset it while it
	 is still transferring data.
	 kradInterrupt will reprogram the timer to
	 TM1D = 65536 - DMABUFFERSIZE/2
	 on first occurance.
	 (DMABUFFERSIZE/2 because we want to get a notification when half the buffer has
	  been played).
	*/
	// HP3-GBA: upstream 65536 - (DMABUFFERSIZE/2) + 32 - 3; kradInterrupt
	// reprograms the timer to 65536 - DMABUFFERSIZE
	TM1D = 65536 - DMABUFFERSIZE + 32 - 3;

	// enable | generate interrupt | count-up timing
	TM1CNT = ( 1 << 7 ) | ( 1 << 6 ) | ( 1 << 2 );

	// SAMPLEFREQ hz (2^24/f)
	TM0D = 65536 - (1<<24>>SAMPLEFREQEXP);

	currMixBlock = 2;
	nextSample = 2*SAMPLESPERFRAME;

	lastDmaBlock = 0;	// HP3-GBA: added
	dmaBlock = 0;
}

u32 LONG_CALL getDmaAddress( s8 **left, s8 **right )
{
	if( !active )
		return 0;

	// HP3-GBA: upstream returns 0 when dmaBlock == ( currMixBlock >> 1 ),
	// before setting the addresses
	*left = &lBuffer[ nextSample ];
	*right = &rBuffer[ nextSample ];

	if( dmaBlock != lastDmaBlock ) {
		lastDmaBlock = dmaBlock;
		if( currMixBlock != 1 && currMixBlock != 2 )
			return 0;
	}

	u32 fit = SAMPLESPERFRAME;
	nextSample += fit;

	if( ++currMixBlock >= BUFFERBLOCKS ) {
		currMixBlock = 0;
		nextSample = 0;
	}

	return fit;
}

void kradActivate()
{
	// allow timer1-interrupts
	INT_IE |= ( 1 << 4 );

	// start timer 0
	TM0CNT = ( 1 << 7 );

	active = 1;
}

void kradDeactivate()
{
	// disable timer 0
	TM0CNT &= ~( 1 << 7 );
	active = 0;
}

// HP3-GBA: no dsDeInit()
