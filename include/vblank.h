#pragma once

#include "types.h"

// g_pVBlankState is set by InitInterruptSystem to &g_VBlankState (US
// 0x03003530) and read by every interrupt handler (HandleVBlankInterrupt,
// HandleHBlankInterrupt, HandleTimer0Interrupt, HandleTimer3OrSerialInterrupt,
// HandleVCountInterrupt) -- not RNG-specific, despite Mt19937AutoSeed also
// reading dwVBlankCount for entropy. Only HandleVBlankInterrupt is confirmed
// to write it; extent past 0x38 unconfirmed.
typedef struct {
    void *pVBlankCallback;  // 0x00: user callback, invoked by HandleVBlankInterrupt if set
    u8    unk04[0x18];      // 0x04: unconfirmed
    u32   dwVBlankCount;    // 0x1C: incremented every real vblank
    u32   dwVBlankConsumed; // 0x20: last dwVBlankCount value WaitForVBlank consumed
    u8    unk24[0x8];       // 0x24: unconfirmed
    u32   dwPlaytimeTick;   // 0x2C: increments every vblank, rolls over past 59
    u32   unk30;            // 0x30: cleared on dwPlaytimeTick rollover
    u32   unk34;            // 0x34: receives the old unk30 on dwPlaytimeTick rollover
    u16   wSuppressOamSwap; // 0x38: gates the OAM double-buffer swap path; cleared by AgbMain at boot
} VBlankState;

extern VBlankState *g_pVBlankState;
