#pragma once

#include "types.h"
#include "actor.h"

// The actorType 3 static tile record returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordSwitch {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8;
    u8 bVariant;          // 0x09, sprite and trigger kind, 0-11; see TickSwitchActor
    u16 wRearmDelay;      // 0x0A, scaled by 30 into SwitchActorState.nRearmTicks
    u8 bInitialFrame;     // 0x0C, variants 9 and 10 start on frame 1 when set
    u8 bKeepOff;          // 0x0D, initial SwitchActorState.bKeepOff
    u8 bOnRespawnGroup;   // 0x0E, RespawnGroupAndRunChain arguments run when it turns on
    u8 bOnChain;          // 0x0F
    u8 bOffRespawnGroup;  // 0x10, run when it turns back off
    u8 bOffChain;         // 0x11
} RoomActorRecordSwitch;

// Actor 0x60-0x6F of a switch.
typedef struct SwitchActorState {
    s32 nRearmTicks;     // 0x60, action state 3 wait of variants 2, 4 and 5
    s32 nPlateFlipping;  // 0x64, variant 1: set while the plate flips
    s32 nPlatePressed;   // 0x68, variant 1: set by HandleSwitchActorTouch, cleared each tick
    s8 bStep;            // 0x6C, animation frame step: 1 while off, -1 while on
    u8 bFrame;           // 0x6D
    u8 pad_6E;
    u8 bKeepOff;         // 0x6F, variant 11 turns on while 0 and off while nonzero
} SwitchActorState;

#define SWITCH_STATE(pActor) ((SwitchActorState *)&(pActor)->scriptState)

extern Actor *SpawnSwitchActor(u8 bColumn, u8 bRow);
extern void TickSwitchActor(Actor *pActor);
extern void HandleSwitchActorTouch(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomSwitchSprites[5];                // ROM 0x0806C178 (US)
extern const ActorGfxRecord *const g_apRoomSwitchAssetRecords[12];  // ROM 0x0806C1A0 (US)
extern const void *const g_apRoomSwitchEffectData[12];               // ROM 0x0806C1D0 (US)
extern const u8 g_aabUnusedRoomSwitchAnims[12][20];                // ROM 0x0806C200 (US)

// 1 while RestoreRoomActorState respawns the room's saved actors, and set
// when the overworld pushes a pause menu. Switches flipping while it is set,
// and the first flip of one spawned while it is set, play no sound.
extern u8 g_bRestoringRoomActors;

extern s32 g_nSwitchSoundHandle;  // handle of the switch flip sound
