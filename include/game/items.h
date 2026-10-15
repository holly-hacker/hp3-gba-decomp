#pragma once

#include "types.h"
#include "constants/items.h"

// dwCategory. The table is laid out as contiguous per-category runs --
// see docs/formats/items.md's "Item categories" section. 12 (0xC) appears
// only on the dummy end-of-list record (index 79).
typedef enum {
    ItemCategoryBelt       = 0,
    ItemCategoryCharm      = 1,
    ItemCategoryGloves     = 2,
    ItemCategoryBoots      = 3,
    ItemCategoryCap        = 4,
    ItemCategoryRobe       = 5,
    ItemCategoryPotion     = 6,
    ItemCategoryBooks      = 7,  // no items; its Items-screen label exists
    ItemCategoryMisc       = 8,  // key items
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

// ItemStats.potion.nEffect.
typedef enum {
    PotionEffectStamina   = 1,  // restores nMagnitude Stamina
    PotionEffectMagic     = 2,  // restores nMagnitude Magic
    PotionEffectPoison    = 3,  // cures poison
    PotionEffectParalysis = 4,  // cures paralysis
} PotionEffect;

// ItemEntry +0x24: equipment stats, or what a potion does.
typedef union {
    struct {
        s32 nDefenseX2;  // Def stat, pre-doubled
        s32 nAgility;    // Agi stat, signed
    } equipment;
    struct {
        s32 nEffect;     // PotionEffect
        s32 nMagnitude;  // Stamina or Magic restored per potion
    } potion;
} ItemStats;

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
    u32 dwFlags;             // 0x20 -- bit 2: consumable (potions); bits 0 and 1
                             // unread (see docs/formats/items.md)
    ItemStats stats;         // 0x24
    u32 dwUnk2C;             // 0x2C -- unidentified
    s32 nMagicDefense;       // 0x30 -- M.Def stat
} ItemEntry;

// BuildFilteredItemList filters besides a plain ItemCategory.
#define ITEM_FILTER_NON_EQUIPMENT 10  // categories from ItemCategoryPotion up
#define ITEM_FILTER_SELLABLE      11  // nonzero nSellPrice

#define EQUIP_SLOT_COUNT 6

// The player's items, saved whole. See docs/formats/save.md.
typedef struct {
    // Owned count per item id, indexed by reward id (see rewards.h), which
    // extends past the last real item.
    u8 abQuantities[ITEM_COUNT];
    // Equipped item id per FighterType and slot (belt, charm, gloves, boots,
    // hat, cloak), 0xFF when empty.
    u8 aabEquipped[3][EQUIP_SLOT_COUNT];
    u8 abPad[2];
} ItemInventory;

extern ItemInventory g_ItemInventory;  // 0x030037B0

#define SAVE_ITEM_QUANTITIES_SIZE sizeof(ItemInventory)
