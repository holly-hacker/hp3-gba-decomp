#include "types.h"
#include "room_script.h"

typedef struct RemovePartyFollowerRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} RemovePartyFollowerRecord;

void RoomScriptOpRemovePartyFollower(RemovePartyFollowerRecord *pRecord)
{
    sub_080236DC(pRecord->bCharacterId);
}
