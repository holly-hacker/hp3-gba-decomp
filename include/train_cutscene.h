#pragma once

#include "types.h"

extern u16 g_wCoolTrainTimer;  // 0x03005E14: frames left before the cutscene ends

extern const u32 g_dwCoolTrainBg0Control;

void InitializeCoolTrainCutscene(void);
void UpdateCoolTrainCutscene(void);
void ExitCoolTrainCutscene(void);
