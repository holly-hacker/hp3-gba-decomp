#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct CancelObjectAnimSequenceRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} CancelObjectAnimSequenceRecord;

void RoomScriptOpCancelObjectAnimSequence(CancelObjectAnimSequenceRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject != NULL)
    {
        CancelObjectMove_candidate(pObject);
        pObject->bAnimFrameCounter = 0;
        if (pObject->pLinkedObject_candidate != NULL)
            pObject->pLinkedObject_candidate->bAnimFrameCounter = 0;
        if (g_dwPendingCameraFocusFlag != 0)
            RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
        SetObjectActionState(pObject, 0);
        SetObjectAnimSubState_candidate(g_pPlayerObject, 0);
    }
}
