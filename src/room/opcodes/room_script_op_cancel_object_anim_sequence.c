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
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject != NULL)
    {
        CancelActorMove_candidate(pObject);
        pObject->anim.bAnimFrameCounter = 0;
        if (pObject->pLinkedActor_candidate != NULL)
            pObject->pLinkedActor_candidate->anim.bAnimFrameCounter = 0;
        if (g_dwPendingCameraFocusFlag != 0)
            RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
        SetActorActionState(pObject, 0);
        SetActorAnimSubState_candidate(g_pPlayerObject, 0);
    }
}
