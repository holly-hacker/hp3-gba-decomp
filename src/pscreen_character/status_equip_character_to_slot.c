#include "pscreen_character.h"
#include "battle/battle.h"

u8 StatusEquipCharacterToSlot(u32 character)
{
    switch (character)
    {
    case Harry:
        return 1;
    case Hermione:
        return 0;
    case Ron:
        return 2;
    default:
        return 0xFF;
    }
}
