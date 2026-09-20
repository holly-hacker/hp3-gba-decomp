#include "types.h"
#include "overworld.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpCancelObjectAnimSequence(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

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
