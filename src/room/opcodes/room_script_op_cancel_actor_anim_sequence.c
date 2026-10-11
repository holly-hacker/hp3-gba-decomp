#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct CancelActorAnimSequenceRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} CancelActorAnimSequenceRecord;

void RoomScriptOpCancelActorAnimSequence(CancelActorAnimSequenceRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
    {
        CancelActorMove_candidate(pActor);
        pActor->anim.bAnimFrameCounter = 0;
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->anim.bAnimFrameCounter = 0;
        if (g_dwPendingCameraFocusFlag != 0)
            RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
        SetActorActionState(pActor, 0);
        SetActorPrevActionState(g_pPlayerActor, 0);
    }
}
