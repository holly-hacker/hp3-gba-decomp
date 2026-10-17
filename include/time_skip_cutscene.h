#pragma once

#include "types.h"
#include "actor.h"

// BG0-BG2 control words shared by the Hogwarts Up Night and Clock Skip cutscenes.
extern const u32 g_dwUpNightBg0Control;  // 0x0806BD98
extern const u32 g_dwUpNightBg1Control;  // 0x0806BD9C
extern const u32 g_dwUpNightBg2Control;  // 0x0806BDA0

extern const ActorAssetRecord g_ClockSkipActor1Asset;  // 0x0806BDA4
extern const ActorAssetRecord g_ClockSkipActor2Asset;  // 0x0806BDB4
extern const u8 g_ClockSkipAnimData[2][54];              // 0x0806BDC4, one per actor

void InitializeClockSkipCutscene(void);
void InitializeHogwartsUpNightCutscene(void);
void UpdateHogwartsUpNightCutscene(void);
void UpdateClockSkipCutscene(void);
void ExitClockSkipCutscene(void);
void ExitHogwartsUpNightCutscene(void);
