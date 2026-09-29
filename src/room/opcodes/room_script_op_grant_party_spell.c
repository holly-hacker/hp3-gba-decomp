#include "types.h"
#include "battle/battle.h"
#include "overworld/room_script.h"

typedef struct GrantPartySpellRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} GrantPartySpellRecord;

void RoomScriptOpGrantPartySpell(GrantPartySpellRecord *pRecord)
{
    u32 slot = GetPartyMasterStatsSlot_candidate(pRecord->bCharacterId);
    u32 count = g_aPartyMasterStats[slot].bKnownSpellCount;
    u32 next = count;

    if (slot != 1)
        next = count + 1;
    if (next <= 6)
        g_aPartyMasterStats[slot].bKnownSpellCount = count + 1;
}
