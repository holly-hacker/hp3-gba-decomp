#pragma once

#include "types.h"

// Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
// handler, not just HandleVBlankInterrupt.
typedef struct {
    void *pVBlankCallback;    // 0x00: user callback, invoked if set
    void *pHBlankCallback;    // 0x04: invoked by HandleHBlankInterrupt_candidate if set
    void *pVCountCallback;    // 0x08: invoked by HandleVCountInterrupt if set
    u8    unk0C[0x10];        // 0x0C: unconfirmed
    u32   dwVBlankCount;      // 0x1C: incremented once per real vblank
    u32   dwVBlankConsumed;   // 0x20: last dwVBlankCount value WaitForVBlank consumed
    u32   dwHBlankCount;      // 0x24: incremented once per HBlank interrupt
    u32   dwVCountCount;      // 0x28: incremented once per VCount interrupt
    u32   dwSecondTick;       // 0x2C: counts 0-59 real vblanks, then rolls over
    u32   dwFrameCounter;     // 0x30: incremented once per logic tick by TickGameModeStack
    u32   dwFramesLastSecond; // 0x34: dwFrameCounter snapshot on dwSecondTick rollover; no reader found
    u16   wOamFrameReady;     // 0x38: set by HideUnusedOamEntries once a frame's OAM is built; nonzero
                               //       makes HandleVBlankInterrupt swap the OAM shadow buffers this
                               //       vblank instead of re-flushing the current one, then clear it
} VBlankState;

extern VBlankState *g_pVBlankState;
extern VBlankState g_VBlankState;
extern void WaitForVBlank(void);
extern void WaitForVBlankIntr(void);
extern void SetVBlankCallback(void *callback);
extern void VBlankCallback(void);  // default callback: tile upload commits
extern void SetVCountCallback(void *callback);
extern void EnableVCountInterrupt(u32 line);
extern void HandleVBlankInterrupt(void);

// See ram_symbols.us.inc: 0x03003B48, read only by WaitForVBlank and
// written only by AgbMain -- the frame-pacing target WaitForVBlank busy-waits up to.
extern u32 g_dwFrameSyncTarget;

// Reentrancy guard for HandleVBlankInterrupt; body only runs while this
// reads back as 1. volatile: real re-reads it instead of caching it in a
// register after the increment.
extern volatile u32 g_dwVBlankIntrNestCount;
// XORed with 1 once per serviced vblank; selects which 0x400-byte half of
// the current 0x800-byte OAM shadow buffer gets DMA'd out.
extern u32 g_bOamDmaHalfToggle;
// Nonzero forces one extra sub_08007130 call this vblank; cleared right after.
extern u32 g_bForcePendingBgWritesFlush;
// Sticky software copy of acked hardware IF bits, ORed in by every
// interrupt handler after acking its own bit in IF.
extern u16 g_wPendingIntrFlags;
