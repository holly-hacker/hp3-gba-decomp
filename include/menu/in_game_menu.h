#pragma once

#include "types.h"
#include "game/game_modes.h"
#include "menu/menu.h"

extern const ListMenuEntry g_aInGameMenuEntries[6];  // 0x08068C38
extern const ListMenuRowObject g_aInGameMenuRowObjects[6];  // 0x08068C80
extern const ListMenuDefinition g_InGameMenuDefinition;  // 0x08068CE0

extern GameMode g_StatusEquipReturnMode;  // 0x03005298: StatusEquipCharacterSelect's B target
extern GameMode g_StatusEquipNextMode;    // 0x0300529C: StatusEquipCharacterSelect's A target

extern void BeginPauseMenuScreen(u32 arg);
extern void StartMenuFadeIn(void);
extern void StartMenuOverlayFadeIn(void);
extern void StartMenuOverlayFadeOut(void);
extern void TickMenuFadeOut(void);
extern void SelectInGameMenuEntry_candidate(void);
extern void sub_0803232C(void);
extern void DrawPauseMenuObjective(void);
extern void sub_080323AC(void);
extern void sub_080323B0(void);
