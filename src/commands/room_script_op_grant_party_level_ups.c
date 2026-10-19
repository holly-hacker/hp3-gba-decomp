#include "types.h"
#include "combat_fighter.h"
#include "commands.h"

typedef struct GrantPartyLevelUpsRecord {
    u32 dwOpcode;
    u8 bLevelCount;
} GrantPartyLevelUpsRecord;

void RoomScriptOpGrantPartyLevelUps(GrantPartyLevelUpsRecord *pRecord)
{
    s32 i;

    for (i = 0; i < pRecord->bLevelCount; i++)
    {
        LevelUpPartyMember(0);
        LevelUpPartyMember(1);
        LevelUpPartyMember(2);
    }
}
