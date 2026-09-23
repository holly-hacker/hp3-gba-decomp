#pragma once

#include "types.h"
#include "game_modes.h"

// Pause menu Items screen, game modes 0x10-0x12; see
// docs/memory-map/game_modes.md.

// Section select (mode 0x10). Each row selects an item list filter: 0xA
// (all non-equipment items), ItemCategoryPotion or ItemCategoryIngredient.
extern const u32 g_aItemsSectionFilters[3];      // 0x0806B1B4
extern const u8 g_ItemsSectionMenuDefinition[];  // 0x0806B1F0

extern GameMode g_ItemsSectionSelectNextMode;  // 0x030054E4: mode pushed once the fade-out finishes
extern s8 g_bItemsSectionCursor;               // 0x030054E8: section row saved on exit

// Item select (mode 0x11).
typedef struct {
    u32 dwHasItems;     // 0x00: nonzero when the filtered item list is not empty
    GameMode nextMode;  // 0x04: mode pushed once the fade-out finishes
    u32 dwFilter;       // 0x08: item list filter, from g_aItemsSectionFilters
} ItemsItemSelectState;

extern ItemsItemSelectState g_ItemsItemSelect;  // 0x030054D8

extern void SetItemsItemSelectFilter(u32 filter);
extern void sub_0803975C(u32 item);  // draws the description of the item under the cursor
extern void sub_080397FC(void);      // clears the description box
extern u32 sub_08039818(void);       // nonzero when the item under the cursor restores Stamina or Magic

// Item use (mode 0x12).
extern u32 g_dwItemUseItem;      // 0x030054EC: item chosen in item select
extern u32 g_dwItemUseQuantity;  // 0x030054F0: quantity chosen in QuantitySelectScreen

extern void SetItemUseItem(u32 item);
extern void sub_08039A20(u32 textId);  // draws the result message under the Items header

// Scrolling item list shared with the Status/Equip item select.
extern u32 sub_08027AF4(u32 filter, s32 x, s32 y, u32 arg3, u32 arg4, u32 arg5, s32 arg6);
extern u32 sub_08027BDC(void);  // item under the list cursor
extern void sub_08027C08(void (*onCursorMove)(u32 item), void (*onClear)(void));

extern u32 sub_08026D34(s32 item);  // g_pItemTable[item].dwUnk20 bit 2
// Restores the member's Stamina or Magic with the item, consumes the units
// needed and returns the result message (0x400 Stamina, 0x401 Magic, 0x403 full).
extern u32 sub_080269E0(u8 character, s32 item, s32 quantity);
extern void sub_0801E05C(u32 titleTextId, u32 cursorKind, u32 arg2);
