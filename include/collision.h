#pragma once

#include "types.h"
#include "actor.h"

extern void HandleDoorTouch(Actor *pSelf, Actor *pOther);
extern void BlockActorWithTerrainBox(Actor *pSelf, Actor *pOther);
extern void HandlePausingActorTouch(Actor *pSelf, Actor *pOther);
extern void HandleContactTriggerTouch(Actor *pSelf, Actor *pOther);
