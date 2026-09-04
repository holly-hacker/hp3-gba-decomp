#pragma once

#include "types.h"

extern void *gIntrVectorPtr;

// 13 x u32 function-pointer dispatch slots, indexed by IntrMain (see its
// decompile: vblank, vcount, timer1, hblank, timer0, timer2, dma0, dma1,
// dma2, dma3, keypad, dummy, serialTimer3). Refreshed from a ROM template
// by InitInterruptSystem.
extern u32 gIntrTable[13];

// ROM copy of gIntrTable's reset contents, DMA3-copied into it by
// InitInterruptSystem.
extern const u32 gIntrTableTemplate[13];

// 0x200-byte IWRAM buffer InstallInterruptHandler CpuSets the live handler
// code into; gIntrVectorPtr points here.
extern u8 gIntrHandlerIwram[0x200];

extern void IntrMain(void);

void InstallInterruptHandler(void *handlerCode);
void InitInterruptSystem(void);
