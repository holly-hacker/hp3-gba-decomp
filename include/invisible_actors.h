#pragma once

#include "types.h"
#include "actor.h"

extern Actor *SpawnTriggerRectActor(u8 bColumn, u8 bRow);
extern Actor *SpawnTriggerZoneActor(u8 bColumn, u8 bRow);
extern void TickTriggerZoneActor(Actor *pActor);
extern void HandleTriggerZoneTouch(Actor *pSelf, Actor *pOther);
extern void HandleTriggerZoneWorldActorTouch(Actor *pSelf, Actor *pOther);
