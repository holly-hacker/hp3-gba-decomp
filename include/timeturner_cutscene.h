#pragma once

#include "types.h"
#include "actor.h"
#include "math.h"
#include "overworld/room.h"

// The mode's screen state at 0x03005D98 (US).
typedef struct {
    FixedPoint cameraDelta;  // 0x00: passed to OffsetCameraFocus; y is the 16.16 fixed-point progress
    u32 bRising;          // 0x08: 1 while progress rises, 0 once it falls back
    Actor *apActors[2];   // 0x0C: see SpawnHarryHermionePortInTimeActor
    u32 dwPositionIndex;  // 0x14: the loaded room; row of g_aHarryHermionePortInTimeActorPos
} HarryHermionePortInTimeState;

extern HarryHermionePortInTimeState g_HarryHermionePortInTime;  // 0x03005D98

// One row per actor position index. The y coordinates are never read; the actors are placed
// relative to the camera focus instead.
typedef struct {
    s32 nActorAX;  // 0x00
    s32 nActorAY;  // 0x04
    s32 nActorBX;  // 0x08
    s32 nActorBY;  // 0x0C
} HarryHermionePortInTimePosition;

extern const HarryHermionePortInTimePosition g_aHarryHermionePortInTimeActorPos[2];  // 0x0806BF40
extern const IntPoint g_aHarryHermionePortInTimeCameraStart[2];
extern const ActorAssetRecord g_aHarryHermionePortInTimeActorAssets[2];
extern const u8 g_aHarryHermionePortInTimeAnims[2][32];
extern const ActorGfxRecord g_HarryHermionePortInTimeShadowGfx;

// The cutscene's start and destination maps, ROM 0x0806BE38 (US).
extern const RoomTableEntry g_aTimeTurnerCutsceneRoomTable[2];

void InitializeHarryHermionePortInTimeCutscene(void);
void UpdateHarryHermionePortInTimeCutscene(void);
void LoadHarryHermionePortInTimeRoom(u32 roomIndex);
void SpawnHarryHermionePortInTimeActor(u32 index);
void ExitHarryHermionePortInTimeCutscene(void);
