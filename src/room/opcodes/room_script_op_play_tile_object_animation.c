#include "types.h"
#include "overworld/room_script.h"

typedef struct PlayTileObjectAnimationRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u16 wAnimId;
} PlayTileObjectAnimationRecord;

void RoomScriptOpPlayTileObjectAnimation(PlayTileObjectAnimationRecord *pRecord)
{
    Object *pObject;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);
    if (g_dwRoomScriptRunState == 2)
        pObject->dwFlags |= ObjectFlagRoomScriptYield;
    SetObjectAnimData_candidate(pObject, pRecord->wAnimId);
    pObject->dwFlags |= ObjectFlagHasAnimation;
}
