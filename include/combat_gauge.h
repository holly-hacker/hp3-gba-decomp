#pragma once

#include "actor.h"

// The SP gauge sprites spawned by SpawnSpGauge: [0] for party members, [1] for enemies.
extern const ActorGfxRecord g_aSpGaugeGfx[2];  // 0x0805BA7C

// Actor bytes 0x60-0x6B of an SP gauge. The gauge counts wValue down by wDrainTotal,
// in steps that grow by wDrainRate / 256 each time.
typedef struct SpGaugeState {
    u16 wValue;       // 0x60, the fighter's wHp at spawn, then the value shown
    u16 wMax;         // 0x62, the fighter's wHp_max
    u16 wDrainTotal;  // 0x64
    u16 wDrained;     // 0x66
    s16 nDrainStep;   // 0x68, 8.8 fixed point
    u16 wDrainRate;   // 0x6A, 8.8 fixed point
} SpGaugeState;

#define SP_GAUGE_STATE(pActor) ((SpGaugeState *)&(pActor)->scriptState)

// bActionSubState of a gauge: fade in, drain, then fade out and destroy.
typedef enum {
    SpGaugeDrain   = 0,
    SpGaugeFadeIn  = 1,
    SpGaugeFadeOut = 2,
} SpGaugeSubState;

extern Actor *SpawnSpGauge(s32 fighterIndex, u32 amount);
extern void TickSpGauge(Actor *gauge);
// Removes the SP gauge of an enemy (isAlly 0) or ally target slot.
extern void DestroySlotSpGauge(u32 slot, u32 isAlly);
extern void DestroyLinkedActor(Actor *actor);
extern void UpdateSpGaugeFrame(Actor *gauge);
