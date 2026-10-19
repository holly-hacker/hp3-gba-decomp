#pragma once

#include "actor.h"

// The SP gauge sprites spawned by SpawnSpGauge.
extern const ActorGfxRecord g_aSpGaugeGfx[2];  // 0x0805BA7C

extern void SpawnSpGauge(s32 fighterIndex, s32 amount);
// Removes the SP gauge of an enemy (isAlly 0) or ally target slot.
extern void DestroySlotSpGauge(u32 slot, u32 isAlly);
extern void DestroyLinkedActor(void *linkedActor);
