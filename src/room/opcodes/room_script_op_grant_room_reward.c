#include "types.h"
#include "overworld/room_script.h"

typedef struct GrantRoomRewardRecord {
    u32 dwOpcode;
    u8 bRewardId;
    u8 bVariant;
} GrantRoomRewardRecord;

void RoomScriptOpGrantRoomReward(GrantRoomRewardRecord *pRecord)
{
    if (pRecord->bVariant != 0)
        sub_08024A88(pRecord->bRewardId);
    else
        sub_08024A30(pRecord->bRewardId);
}
