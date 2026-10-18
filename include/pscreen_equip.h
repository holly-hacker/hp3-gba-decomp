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
    u32 dwItemListOpen;        // 0x14: nonzero while the item list is open
    u32 dwUnk18;               // 0x18
    Actor *apStatArrows[3];    // 0x1C: Def/Agi/M.Def up/down arrows
    u16 awSavedPalette[3];     // 0x28: BG palette colors 4-6, restored on exit
} StatusEquipItemSelectState;

// Def/Agi/M.Def comparison: label x, first row y, row (and line) height, and the
// tile rows cleared before the values are redrawn.
#ifdef VERSION_JP
#define EQUIP_STAT_LABEL_X 0x8E
#define EQUIP_STAT_ROW_Y 0x1C
#define EQUIP_STAT_ROW_HEIGHT 9
#define EQUIP_STAT_CLEAR_ROW 3
#define EQUIP_STAT_CLEAR_ROWS 5
#else
#define EQUIP_STAT_LABEL_X 0x96
#define EQUIP_STAT_ROW_Y 0x20
#define EQUIP_STAT_ROW_HEIGHT 8
#define EQUIP_STAT_CLEAR_ROW 4
#define EQUIP_STAT_CLEAR_ROWS 3
#endif
#define EQUIP_STAT_ROW(n) (EQUIP_STAT_ROW_Y + (n) * EQUIP_STAT_ROW_HEIGHT)

extern StatusEquipItemSelectState g_StatusEquipItemSelect;  // 0x030052C8
extern u32 g_dwStatusEquipSlotType;  // 0x030052C0: equipment type of the chosen slot

extern void InitializeStatusEquipItemSelect(void);
extern void UpdateStatusEquipItemSelect(void);
extern void ExitStatusEquipItemSelect(void);
extern void BeginStatusEquipItemSelectScreen(void);
// Shows the Def/Agi/M.Def values with the slot's current item and with `item` equipped.
extern void DrawEquipItemStatComparison(u32 item);
// Equips the selected item, or empties the slot for the Remove row; returns 0 for an empty list.
extern u32 EquipStatusEquipItemSelection(void);
extern void SelectStatusEquipSlotType(u32 slotType);  // sets g_dwStatusEquipSlotType
