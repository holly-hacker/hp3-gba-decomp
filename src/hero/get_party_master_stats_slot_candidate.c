#include "combat.h"
#include "overworld/room_script.h"

u32 GetPartyMasterStatsSlot_candidate(u32 characterId)
{
    switch (characterId)
    {
    case 1:
    case 6:
        return Hermione;
    case 2:
    case 7:
        return Ron;
    case 8:
        return Buckbeak;
    case 0:
    case 3:
    case 4:
    case 5:
    default:
        return Harry;
    }
}
