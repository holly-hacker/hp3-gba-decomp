#pragma once

#include "types.h"
#include "actor.h"

extern void InitializeHippogriffFliesIntoAirCutscene(void);
extern void UpdateHippogriffFliesIntoAirCutscene(void);
extern void ExitHippogriffFliesIntoAirCutscene(void);

extern Actor *g_pHippogriffFliesIntoAirActor;   // 0x03002F18: the hippogriff; scaled and moved into the air
extern Actor *g_pHippogriffFliesIntoAirActor2;  // 0x03002F1C

extern const u32 g_dwHippogriffFliesIntoAirBg0Control;
extern const ActorAssetRecord g_HippogriffFliesIntoAirAsset;   // the hippogriff
extern const ActorAssetRecord g_HippogriffFliesIntoAirAsset2;
