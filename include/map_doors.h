#pragma once

#include "types.h"
#include "actor.h"

extern Actor *SpawnDoorActor(u8 bColumn, u8 bRow);
extern void HandlePortraitDoorTouch(Actor *pSelf, Actor *pOther);
extern Actor *SpawnPortraitDoorActor(u8 bColumn, u8 bRow);
extern void TickDoorActor(Actor *pActor);
extern s32 GetRoomFloorLevel(s32 roomId);

// The portrait door's exit param, kept while the player crosses
// portrait_room_passage (32) and applied on leaving it.
extern u32 g_dwPortraitPassageExitParam;
