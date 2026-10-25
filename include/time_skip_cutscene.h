#pragma once

#include "types.h"
#include "actor.h"

// BG0-BG2 control words shared by the Hogwarts Up Night and Clock Skip cutscenes.
extern const u32 g_dwUpNightBg0Control;
extern const u32 g_dwUpNightBg1Control;
extern const u32 g_dwUpNightBg2Control;

extern const ActorAssetRecord g_ClockSkipActor1Asset;
extern const ActorAssetRecord g_ClockSkipActor2Asset;
extern const u8 g_ClockSkipAnimData[2][54];              // one per actor

void InitializeClockSkipCutscene(void);
void InitializeHogwartsUpNightCutscene(void);
void UpdateHogwartsUpNightCutscene(void);
void UpdateClockSkipCutscene(void);
void ExitClockSkipCutscene(void);
void ExitHogwartsUpNightCutscene(void);
