#pragma once

#include "types.h"

// Battle-effect script data types; see docs/formats/battle_scripts.md.

// One 0x10-byte background record read by script opcodes 0x7F, 0x8A and 0x8B.
typedef struct EffectBgRecord {
    void *pGfx;         // 0x00
    u16 wUnk04;         // 0x04
    u16 wUnk06;         // 0x06
    void *pControls;    // 0x08
    u16 wUnk0C;         // 0x0C
    u16 pad_0E;         // 0x0E
} EffectBgRecord;

// What EffectBgRecord::pControls points at: an 8-byte control block, then streams.
typedef struct {
    const void *pStream;
    u32 dwTag;
} EffectStreamEntry;
typedef struct {
    u32 adwControls[2];
    EffectStreamEntry entries[32];
} EffectStreamList32;
typedef struct {
    u32 adwControls[2];
    EffectStreamEntry entries[8];
} EffectStreamList8;
