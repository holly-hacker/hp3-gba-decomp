#pragma once

#include "types.h"
#include "actor.h"

// Text actors: SpawnTextActor spawns an actor that draws *ppText and files it in
// g_apTextActors[slot]; SetTextActorCenterPosition_candidate centers it on x.
extern Actor *g_apTextActors[17];  // 0x03005D10
extern Actor *SpawnTextActor(const u8 **ppText, u32 slot);
extern void SetTextActorCenterPosition_candidate(Actor *pActor, s32 x, s32 y);
