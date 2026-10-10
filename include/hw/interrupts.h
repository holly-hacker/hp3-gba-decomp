#pragma once

#include "types.h"

extern void *gIntrVectorPtr;

// 13 x u32 function-pointer dispatch slots, indexed by IntrMain in its
// priority order: timer 3/serial, vblank, vcount, timer 1, hblank, timer 0,
// timer 2, DMA 0-3, keypad, Game Pak (never dispatched; IntrMain hangs).
// Refreshed from a ROM template by InitInterruptSystem.
extern u32 gIntrTable[13];

// ROM copy of gIntrTable's reset contents, DMA3-copied into it by
// InitInterruptSystem.
extern const u32 gIntrTableTemplate[13];

// 0x200-byte IWRAM buffer InstallInterruptHandler CpuSets the live handler
// code into; gIntrVectorPtr points here.
extern u8 gIntrHandlerIwram[0x200];

extern void IntrMain(void);
extern void HandleTimer3Interrupt_candidate(void);
extern void HandleVCountInterrupt(void);
extern void HandleHBlankInterrupt_candidate(void);
extern void HandleTimer0Interrupt_candidate(void);
extern void IwramTimer1Handler(void);  // code in the IWRAM image kramInstall copies from ROM
extern void HandleTimer2Interrupt(void);
extern void IntrDummy(void);

void InstallInterruptHandler(void *handlerCode);
// Stores a handler in gIntrTable[slot].
void SetIntrFunc(u32 slot, void (*pfnHandler)(void));
void InitInterruptSystem(void);
void EnableInterrupts(void);
