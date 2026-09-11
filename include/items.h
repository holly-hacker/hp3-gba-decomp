#pragma once

#include "types.h"

// dwCategory. The table is laid out as contiguous per-category runs --
// see docs/formats/items.md's "Item categories" section. 7 is unused;
// 12 (0xC) appears only on the dummy end-of-list record (index 79).
typedef enum {
    ItemCategoryBelt       = 0,
    ItemCategoryCharm      = 1,
    ItemCategoryGloves     = 2,
    ItemCategoryBoots      = 3,
    ItemCategoryCap        = 4,
    ItemCategoryRobe       = 5,
    ItemCategoryPotion     = 6,
    ItemCategoryIngredient = 8,
    ItemCategoryDummyEnd   = 12,
} ItemCategory;

// nCharacterMask, a bitmask -- CanFighterEquipItem (0x080267D0) ORs
// together the bit for whichever FighterType is equipping. Only read
// for dwCategory < ItemCategoryPotion (see docs/formats/items.md's
// "Equip eligibility" section); items outside that range store 0 here.
typedef enum {
    ItemCharacterMaskNone     = 0,
    ItemCharacterMaskHarry    = 0x1,
    ItemCharacterMaskRon      = 0x2,
    ItemCharacterMaskHermione = 0x4,
} ItemCharacterMask;

// g_pItemTable's per-item record, 0x34 bytes. See docs/formats/items.md
// for how each field was identified.
typedef struct ItemEntry {
    s32 nNameTextId;         // 0x00 -- dialog string id for the display name
    const void *pPalette;    // 0x04 -- icon palette pointer, see docs/formats/graphics.md
    const void *pTileData;   // 0x08 -- icon compressed tile-data pointer
    const void *pFrameData;  // 0x0C -- icon frame/layout header pointer
    s32 nBuyPrice;           // 0x10 -- shop buy price (Sickles)
    s32 nSellPrice;          // 0x14 -- shop sell price (Sickles)
    u32 dwCategory;          // 0x18 -- ItemCategory
    s32 nCharacterMask;      // 0x1C -- ItemCharacterMask bits
    u32 dwUnk20;             // 0x20 -- flag word, bit 2 tested
    s32 nDefenseX2;          // 0x24 -- Def stat, pre-doubled
    s32 nAgility;            // 0x28 -- Agi stat, signed
    u32 dwUnk2C;             // 0x2C -- unidentified
    u32 dwMagicDefense;      // 0x30 -- M.Def stat
} ItemEntry;
extern const ItemEntry g_pItemTable[132];  // 0x08060EE4, US only, src/data/items.c
