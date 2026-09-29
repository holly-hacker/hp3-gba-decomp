#include "types.h"
#include "overworld/room_script.h"

typedef struct ConsumeRoomItemRecord {
    u32 dwOpcode;
    u8 bItemId;
} ConsumeRoomItemRecord;

void RoomScriptOpConsumeRoomItem(ConsumeRoomItemRecord *pRecord)
{
    ConsumeBattleItemSlot(pRecord->bItemId, 1);
}
