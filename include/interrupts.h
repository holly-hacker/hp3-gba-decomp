#pragma once

#include "types.h"

// An interrupt handler or gIntrTable slot.
typedef void (*IntrFunc)(void);

extern void *gIntrVectorPtr;

// 13 dispatch slots, indexed by IntrMain in its priority order: timer
// 3/serial, vblank, vcount, timer 1, hblank, timer 0, timer 2, DMA 0-3,
// keypad, Game Pak (never dispatched; IntrMain hangs).
// Refreshed from a ROM template by InitInterruptSystem.
extern IntrFunc gIntrTable[13];

// ROM copy of gIntrTable's reset contents, DMA3-copied into it by
// InitInterruptSystem.
extern const IntrFunc gIntrTableTemplate[13];

// 0x200-byte IWRAM buffer InstallInterruptHandler CpuSets the live handler
// code into; gIntrVectorPtr points here.
extern u8 gIntrHandlerIwram[0x200];

extern void IntrMain(void);
extern void HandleTimer3Interrupt(void);
extern void HandleVCountInterrupt(void);
extern void HandleHBlankInterrupt(void);
extern void HandleTimer0Interrupt(void);
extern void HandleTimer2Interrupt(void);
extern void IntrDummy(void);

void InstallInterruptHandler(void *handlerCode);
// Stores a handler in gIntrTable[slot].
void SetIntrFunc(u32 slot, IntrFunc pfnHandler);
// Restores gIntrTable[slot] from gIntrTableTemplate.
void ResetIntrFunc(u32 slot);
void InitInterruptSystem(void);
void EnableInterrupts(void);

// Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
// handler, not just HandleVBlankInterrupt.
typedef struct {
    void (*pVBlankCallback)(void);  // 0x00: user callback, invoked if set
    void (*pHBlankCallback)(void);  // 0x04: invoked by HandleHBlankInterrupt if set
    void (*pVCountCallback)(void);  // 0x08: invoked by HandleVCountInterrupt if set
    u32   dwTimer0Count;            // 0x0C: incremented once per Timer 0 interrupt
    u8    abUnused[0x8];            // 0x10: no access found
    u32   dwTimer3Count;            // 0x18: incremented once per Timer 3 interrupt
    u32   dwVBlankCount;            // 0x1C: incremented once per real vblank
    u32   dwVBlankConsumed;         // 0x20: last dwVBlankCount value WaitForVBlank consumed
    u32   dwHBlankCount;            // 0x24: incremented once per HBlank interrupt
    u32   dwVCountCount;            // 0x28: incremented once per VCount interrupt
    u32   dwSecondTick;             // 0x2C: counts 0-59 real vblanks, then rolls over
    u32   dwFrameCounter;           // 0x30: incremented once per logic tick by TickGameModeStack
    u32   dwFramesLastSecond;       // 0x34: dwFrameCounter snapshot on dwSecondTick rollover; no reader found
    u16   wOamFrameReady;           // 0x38: set by HideUnusedOamEntries once a frame's OAM is built; nonzero
                                    //       makes HandleVBlankInterrupt swap the OAM shadow buffers this
                                    //       vblank instead of re-flushing the current one, then clear it
} VBlankState;

extern VBlankState *g_pVBlankState;
extern VBlankState g_VBlankState;
extern void WaitForVBlankIntr(void);
extern void SetVBlankCallback(void (*callback)(void));
extern void VBlankCallback(void);  // default callback: tile upload commits
extern void SetHBlankCallback(void (*callback)(void));
extern void SetVCountCallback(void (*callback)(void));
extern void EnableVCountInterrupt(u32 line);
extern void DisableVCountInterrupt(void);
// Reinstalls VBlankCallback as the vblank callback.
extern void RestoreDefaultVBlankCallback(void);
extern void HandleVBlankInterrupt(void);

// Reentrancy guard for HandleVBlankInterrupt; body only runs while this
// reads back as 1. volatile: real re-reads it instead of caching it in a
// register after the increment.
extern volatile u32 g_dwVBlankIntrNestCount;
// XORed with 1 once per serviced vblank; selects which 0x400-byte half of
// the current 0x800-byte OAM shadow buffer gets DMA'd out.
extern u32 g_bOamDmaHalfToggle;
// Sticky software copy of acked hardware IF bits, ORed in by every
// interrupt handler after acking its own bit in IF.
extern u16 g_wPendingIntrFlags;
