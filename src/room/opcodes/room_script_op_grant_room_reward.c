#include "types.h"
#include "overworld/room_script.h"

typedef struct GrantRoomRewardRecord {
    u32 dwOpcode;
    u8 bRewardId;
    u8 bVariant;
} GrantRoomRewardRecord;

// Both callees start the player's "receive item" action state (0x17) and grant the reward;
// the count is a random 30-60 roll only for reward 0x83. The variant path also sets +0x80 to
// 0x42. Every script passes variant 0.
void RoomScriptOpGrantRoomReward(GrantRoomRewardRecord *pRecord)
{
    if (pRecord->bVariant != 0)
        PlayerReceiveRewardAlt(pRecord->bRewardId);
    else
        PlayerReceiveReward(pRecord->bRewardId);
}
