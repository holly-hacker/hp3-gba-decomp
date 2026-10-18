#include "pscreen_character.h"
#include "battle/battle.h"

u8 StatusEquipSlotToCharacter(u8 slot)
{
    switch (slot)
    {
    case 0:
        return Hermione;
    case 1:
        return Harry;
    case 2:
        return Ron;
    }
    return 0xFF;
}
