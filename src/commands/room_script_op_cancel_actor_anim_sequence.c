#include "types.h"
#include "area.h"
#include "commands.h"
#include "move.h"
#include "hero.h"

typedef struct CancelActorAnimSequenceRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} CancelActorAnimSequenceRecord;

void RoomScriptOpCancelActorAnimSequence(CancelActorAnimSequenceRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
    {
        CancelActorMove_candidate(pActor);
        pActor->anim.bAnimFrameCounter = 0;
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->anim.bAnimFrameCounter = 0;
        if (g_dwFieldSpellActive != 0)
            EndFieldSpellEffect(g_pFieldSpellEffectActor);
        SetActorActionState(pActor, 0);
        SetActorPrevActionState(g_pPlayerActor, 0);
    }
}
