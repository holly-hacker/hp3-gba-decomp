#pragma once

#include "modes.h"
#include "actor.h"

// Status/Equip item select (mode 0x0F); see docs/memory-map/game_modes.md.
typedef struct {
    u32 dwUnk0;                // 0x00
    GameMode nextMode;         // 0x04: mode pushed once the fade-out finishes
    u32 dwTextCursor;          // 0x08: text tile cursor after the stat labels
    u32 dwUnkC;                // 0x0C
    u32 dwHasItems;            // 0x10: nonzero when an item list was built
    void *pItemList;           // 0x14: item list menu, or NULL
    u32 dwUnk18;               // 0x18
    Actor *apStatArrows[3];   // 0x1C: Def/Agi/M.Def up/down arrows
    u16 awSavedPalette[3];     // 0x28: BG palette colors 4-6, restored on exit
} StatusEquipItemSelectState;

extern StatusEquipItemSelectState g_StatusEquipItemSelect;  // 0x030052C8
extern u32 g_dwStatusEquipSlotType;  // 0x030052C0: equipment type of the chosen slot

extern void InitializeStatusEquipItemSelect(void);
extern void UpdateStatusEquipItemSelect(void);
extern void ExitStatusEquipItemSelect(void);
extern void sub_080362D8(void);
extern u32 sub_080368E4(void);
extern void sub_080368CC(u32 slotType);  // sets g_dwStatusEquipSlotType
