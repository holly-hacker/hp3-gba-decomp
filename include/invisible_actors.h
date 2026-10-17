#pragma once

#include "types.h"
#include "actor.h"

extern Actor *SpawnTriggerRectActor(u8 bColumn, u8 bRow);
extern Actor *SpawnTriggerZoneActor(u8 bColumn, u8 bRow);
extern void sub_080264F0(Actor *pActor);
extern void sub_080265B8(Actor *pSelf, Actor *pOther);
extern void sub_08026674(Actor *pSelf, Actor *pOther);
