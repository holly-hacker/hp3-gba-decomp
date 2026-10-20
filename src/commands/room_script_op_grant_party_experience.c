#include "types.h"
#include "commands.h"
#include "map_experience.h"

typedef struct GrantPartyExperienceRecord {
    u32 dwOpcode;
    u16 wExperience;
} GrantPartyExperienceRecord;

void RoomScriptOpGrantPartyExperience(GrantPartyExperienceRecord *pRecord)
{
    GrantPartyExperience(pRecord->wExperience);
}
