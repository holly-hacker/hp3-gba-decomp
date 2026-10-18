#include "types.h"
#include "combat.h"
#include "items.h"
#include "items_inline.h"

u32 CanFighterEquipItem(u8 character, u32 item)
{
    switch (character)
    {
    case Harry:
        if ((GetItemCharacterMaskInline(item) & ItemCharacterMaskHarry) == 0)
            return 0;
        break;
    case Hermione:
        if ((GetItemCharacterMaskInline(item) & ItemCharacterMaskHermione) == 0)
            return 0;
        break;
    case Ron:
        if ((GetItemCharacterMaskInline(item) & ItemCharacterMaskRon) == 0)
            return 0;
        break;
    }

    return 1;
}
