#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct SetTileActorAnimStateRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileActorAnimStateRecord;

void RoomScriptOpSetTileActorAnimState(SetTileActorAnimStateRecord *pRecord)
{
    SetActorActionState(GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY), 4);
}
