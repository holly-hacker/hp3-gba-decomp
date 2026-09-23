#pragma once

#include "types.h"
#include "object.h"

// The mode's screen state at 0x03005D98 (US). Fields used by the mode handlers;
// the object setup helpers sub_08043114/sub_08043308 own the rest.
typedef struct {
    u32 dwUnk0;           // 0x00: first argument of sub_0800A420
    s32 nProgress;        // 0x04: 16.16 fixed-point, second argument of sub_0800A420
    u32 bRising;          // 0x08: 1 while progress rises, 0 once it falls back
    Object *pObjectA;     // 0x0C
    Object *pObjectB;     // 0x10
    u32 dwPositionIndex;  // 0x14: row of g_aHarryHermionePortInTimeObjectPos
} HarryHermionePortInTimeState;

extern HarryHermionePortInTimeState g_HarryHermionePortInTime;  // 0x03005D98

// One row per position index: the x coordinate of object A at +0x00 and of object B at +0x08.
typedef struct {
    s32 nObjectAX;    // 0x00
    s32 dwUnk4;       // 0x04
    s32 nObjectBX;    // 0x08
    s32 dwUnk0xC;     // 0x0C
} HarryHermionePortInTimePosition;

extern const HarryHermionePortInTimePosition g_aHarryHermionePortInTimeObjectPos[];  // 0x0806BF40

extern void sub_08043114(u32 arg);
extern void sub_08043308(u32 arg);
extern void sub_0803EA3C(void);
