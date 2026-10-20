#include "game/items.h"
#include "hero.h"

// The ItemCharacterMask bit of a character's stats slot; 0 for Buckbeak and an empty slot.
s32 GetCharPresenceBit(u8 characterId)
{
    switch (characterId)
    {
    case 0:
    case 3:
    case 4:
        return ItemCharacterMaskHarry;
    case 5:
        return ItemCharacterMaskHarry;
    case 1:
    case 6:
        return ItemCharacterMaskHermione;
    case 2:
    case 7:
        return ItemCharacterMaskRon;
    case 8:
    case 0xFF:
        return ItemCharacterMaskNone;
    default:
        return -1;
    }
}
