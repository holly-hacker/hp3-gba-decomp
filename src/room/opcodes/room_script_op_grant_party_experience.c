#include "types.h"
#include "overworld/room_script.h"

typedef struct GrantPartyExperienceRecord {
    u32 dwOpcode;
    u16 wExperience;
} GrantPartyExperienceRecord;

void RoomScriptOpGrantPartyExperience(GrantPartyExperienceRecord *pRecord)
{
    GrantPartyExperience_candidate(pRecord->wExperience);
}
