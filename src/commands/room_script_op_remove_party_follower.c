#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct RemovePartyFollowerRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} RemovePartyFollowerRecord;

void RoomScriptOpRemovePartyFollower(RemovePartyFollowerRecord *pRecord)
{
    RemovePartyMember(pRecord->bCharacterId);
}
