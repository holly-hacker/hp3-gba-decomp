#pragma once

#include "types.h"
#include "game_modes.h"
#include "menu.h"

extern const ListMenuEntry g_aInGameMenuEntries[6];  // 0x08068C38
extern const ListMenuDefinition g_InGameMenuDefinition;  // 0x08068CE0

extern GameMode g_StatusEquipReturnMode;  // 0x03005298: StatusEquipCharacterSelect's B target
extern GameMode g_StatusEquipNextMode;    // 0x0300529C: StatusEquipCharacterSelect's A target

extern void sub_08031FB8(u32 arg);
extern void sub_080320A4(void);
extern void sub_0803217C(void);
extern void sub_080321A8(void);
extern void SelectInGameMenuEntry_candidate(void);
extern void sub_0803232C(void);
extern void sub_0803233C(void);
extern void sub_080323AC(void);
extern void sub_080323B0(void);
