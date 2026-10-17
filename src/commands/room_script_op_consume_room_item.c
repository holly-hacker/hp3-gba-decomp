#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"
#include "items.h"

typedef struct ConsumeRoomItemRecord {
    u32 dwOpcode;
    u8 bItemId;
} ConsumeRoomItemRecord;

void RoomScriptOpConsumeRoomItem(ConsumeRoomItemRecord *pRecord)
{
    RemoveItems(pRecord->bItemId, 1);
}
