#pragma once

#include "types.h"
#include "game/items.h"
#include "actor.h"

// Defined const in src/items/items.c. Declared without const, as the ROM's
// inventory code was compiled: UseRestorePotion re-reads a field after a call.
extern ItemEntry g_pItemTable[ITEM_COUNT];

// Rolls one Folio Universitas card for a bought Chocolate Frogs and adds it to
// the collection; returns the rolled reward id.
u32 GrantRandomChocolateFrogCard(void);

u32 EquipItemInSlot(u8 character, u32 item);
u32 CanFighterEquipItem(u8 character, u32 item);
void ApplyEquipmentStatModifiers(void);
u32 UnequipItemFromSlot(u8 character, u32 slot);
// Returns the result message (0x400 Stamina, 0x401 Magic, 0x403 already full).
u32 UseRestorePotion(u8 character, s32 item, s32 quantity);
void DebugGrantAllItems(u32 count);

u32 GetRewardNameStringId_candidate(u32 rewardId);
void GetItemImageData(u32 item, const void **ppPalette, const void **ppTileData, const void **ppFrameData);
u32 GetItemBuyPrice(u32 item);
u32 GetItemSellPrice(u32 item);
u32 GetItemCategory(u32 item);
u32 GetItemCharacterMask(u32 item);
s32 GetItemDefenseBoost(u32 item);
s32 GetItemAgility(u32 item);
s32 GetItemMagicDefense(u32 item);

s32 GetPotionEffect(s32 item);
s32 GetPotionMagnitude(s32 item);

u32 IsItemUsableInBattle_candidate(u32 item);
u32 IsItemListedInItemsMenu_candidate(u32 item);
u32 IsItemConsumable(s32 item);

void ClearItemInventoryForNewGame_candidate(void);
void ClearItemInventory(void);
void SerializeItemQuantities(void);
void DeserializeItemQuantities(void);

// Gives `amount` of a reward and returns how many of it the player now has:
// the Sickles total, a card's copy count (amount is ignored), or the item
// count, capped at MAX_ITEM_QUANTITY.
u32 GrantReward(s32 rewardId, u32 amount);

u32 RemoveItems(u32 item, u32 count);
u32 GetItemQuantity(u32 item);
u32 BuildFilteredItemList(u32 filter, u32 *pItems, u32 withRemove);
u32 BuildBattleItemList_candidate(u32 *pItems);
u32 CountOwnedPotionKinds(void);
u32 IsBattleItemSlotUsable(u32 slot);
u32 OwnsItemInCategory(u32 category);
u32 GetEquippedItem(u8 character, u32 slot);
u32 IsFolioPageGroupComplete(u32 pageGroupId);
// Double-size affine with both scales set to step 0..8 of a table: 0x666, then 0x2000 * step.
extern void SetActorScaleStep(Actor *actor, u32 step);
u8 *GetPartyMemberName(s32 character);

extern const u32 g_adwActorScaleSteps[9];
