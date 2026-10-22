#pragma once

#include "types.h"
#include "modes.h"
#include "pause_menu.h"

// Pause menu Items screen, game modes 0x10-0x12.

// Section select (mode 0x10). Each row selects an item list filter: 0xA
// (all non-equipment items), ItemCategoryPotion or ItemCategoryMisc.
extern const ListMenuEntry g_aItemsSectionEntries[3];          // 0x0806B190
extern const u32 g_aItemsSectionFilters[3];                    // 0x0806B1B4
extern const ActorAssetRecord g_aItemsSectionRowActors[3];   // 0x0806B1C0
extern const ListMenuDefinition g_ItemsSectionMenuDefinition;  // 0x0806B1F0

extern void UpdateItemsSectionSelect(void);
extern void InitializeItemsSectionSelect(void);
extern void ExitItemsSectionSelect(void);

extern GameMode g_ItemsSectionSelectNextMode;  // 0x030054E4: mode pushed once the fade-out finishes
extern s8 g_bItemsSectionCursor;               // 0x030054E8: section row saved on exit

// Item select (mode 0x11).
typedef struct {
    u32 dwHasItems;     // 0x00: nonzero when the filtered item list is not empty
    GameMode nextMode;  // 0x04: mode pushed once the fade-out finishes
    u32 dwFilter;       // 0x08: item list filter, from g_aItemsSectionFilters
} ItemsItemSelectState;

extern ItemsItemSelectState g_ItemsItemSelect;  // 0x030054D8

extern void UpdateItemsItemSelect(void);
extern void InitializeItemsItemSelect(void);
extern void ExitItemsItemSelect(void);
extern void SetItemsItemSelectFilter(u32 filter);
extern void DrawItemDescription(u32 item);     // draws the description of the item under the cursor
extern void ClearItemDescription(void);        // clears the description box
extern u32 IsSelectedItemRestorePotion(void);  // nonzero when the item under the cursor restores Stamina or Magic

// Item use (mode 0x12).
extern u32 g_dwItemUseItem;      // 0x030054EC: item chosen in item select
extern u32 g_dwItemUseQuantity;  // 0x030054F0: quantity chosen in QuantitySelectScreen

extern void InitializeItemUseScreen(void);
extern void UpdateItemUseScreen(void);
extern void ExitItemUseScreen(void);
extern void SetItemUseItem(u32 item);
extern void DrawItemUseResult(u32 textId);  // draws the result message under the Items header
