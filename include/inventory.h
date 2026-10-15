#pragma once

#include "types.h"

// Rolls one Folio Universitas card for a bought Chocolate Frogs and adds it to
// the collection; returns the rolled reward id.
u32 GrantRandomChocolateFrogCard(void);

void ClearItemInventory(void);
void ClearItemInventoryForNewGame_candidate(void);
void SerializeItemQuantities(void);
void DeserializeItemQuantities(void);

// Gives `amount` of a reward and returns how many of it the player now has:
// the Sickles total, a card's copy count (amount is ignored), or the item
// count, capped at MAX_ITEM_QUANTITY.
u32 GrantReward(s32 rewardId, u32 amount);
