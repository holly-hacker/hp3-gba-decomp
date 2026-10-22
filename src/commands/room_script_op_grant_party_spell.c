#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"
#include "combat.h"

typedef struct GrantPartySpellRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} GrantPartySpellRecord;

void RoomScriptOpGrantPartySpell(GrantPartySpellRecord *pRecord)
{
    u32 slot = GetPartyMasterStatsSlot_candidate(pRecord->bCharacterId);
    u32 count = g_aPartyMasterStats[slot].stats.bKnownSpellCount;
    u32 next = count;

    if (slot != Hermione)
        next = count + 1;
    if (next <= 6)
        g_aPartyMasterStats[slot].stats.bKnownSpellCount = count + 1;
}
