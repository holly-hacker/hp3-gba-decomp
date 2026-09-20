#include "types.h"
#include "battle.h"
#include "room_script.h"

void RoomScriptOpGrantPartySpell(RoomScriptRecord *pRecord)
{
    u32 slot = GetPartyMasterStatsSlot_candidate(pRecord->operand.ab[0]);
    u32 count = g_aPartyMasterStats[slot].bKnownSpellCount;
    u32 next = count;

    if (slot != 1)
        next = count + 1;
    if (next <= 6)
        g_aPartyMasterStats[slot].bKnownSpellCount = count + 1;
}
