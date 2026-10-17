#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "overworld/room.h"

// The mode's screen state at 0x03005D98 (US). Fields used by the mode handlers;
// the actor setup helpers sub_08043114/sub_08043308 own the rest.
typedef struct {
    FixedPoint cameraDelta;  // 0x00: passed to OffsetCameraFocus; y is the 16.16 fixed-point progress
    u32 bRising;          // 0x08: 1 while progress rises, 0 once it falls back
    Actor *pActorA;     // 0x0C
    Actor *pActorB;     // 0x10
    u32 dwPositionIndex;  // 0x14: row of g_aHarryHermionePortInTimeActorPos
} HarryHermionePortInTimeState;

extern HarryHermionePortInTimeState g_HarryHermionePortInTime;  // 0x03005D98

// One row per position index: the x coordinate of actor A at +0x00 and of actor B at +0x08.
typedef struct {
    s32 nActorAX;    // 0x00
    s32 dwUnk4;       // 0x04
    s32 nActorBX;    // 0x08
    s32 dwUnk0xC;     // 0x0C
} HarryHermionePortInTimePosition;

extern const HarryHermionePortInTimePosition g_aHarryHermionePortInTimeActorPos[2];  // 0x0806BF40

// Entries 0 and 1 of the Time-Turner cutscene's own table, ROM 0x0806BE38 (US).
extern const RoomTableEntry g_aTimeTurnerCutsceneRoomTable[2];

void InitializeHarryHermionePortInTimeCutscene(void);
void UpdateHarryHermionePortInTimeCutscene(void);
extern void sub_08043114(u32 arg);
extern void sub_08043308(u32 arg);
void ExitHarryHermionePortInTimeCutscene(void);
