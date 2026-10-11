#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorDrawLayerRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bPriority;
} SetTileActorDrawLayerRecord;

void RoomScriptOpSetTileActorDrawLayer(SetTileActorDrawLayerRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
        pActor->oam.priority = pRecord->bPriority;
}
