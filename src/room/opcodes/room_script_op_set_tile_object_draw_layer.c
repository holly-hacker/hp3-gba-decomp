#include "types.h"
#include "room_script.h"

typedef struct SetTileObjectDrawLayerRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bPriority;
} SetTileObjectDrawLayerRecord;

void RoomScriptOpSetTileObjectDrawLayer(SetTileObjectDrawLayerRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject != NULL)
        pObject->oam.priority = pRecord->bPriority;
}
