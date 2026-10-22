#include "types.h"
#include "area.h"
#include "trigger_actor.h"

// Room actor constructor for tile actorType 3, a two-state switch (button,
// pressure plate or lever).
Actor *SpawnSwitchActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordSwitch *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocDefaultActor();

    if (pActor != 0)
    {
        SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
        pActor->wActorType = pRecord->dwActorType;
        pActor->dwFlags = ActorFlagHasTickLogic | ActorFlagTickHandlerSuspendsMovement;
        pActor->wCharacterId_candidate = pRecord->bVariant;
        pActor->oam.objMode = 0;
        pActor->oam.bpp8 = 0;
        pActor->oam.priority = 3;
        SetActorPendingPalette(pActor, g_apRoomSwitchEffectData[pActor->wCharacterId_candidate]);
        pActor->bActionState = 0;
        SWITCH_STATE(pActor)->bFrame = 0;
        SWITCH_STATE(pActor)->bStep = 1;
        SWITCH_STATE(pActor)->bKeepOff = pRecord->bKeepOff;
        SWITCH_STATE(pActor)->nRearmTicks = pRecord->wRearmDelay * 30;
        pActor->pfnTick = TickSwitchActor;

        if (pActor->wCharacterId_candidate <= 10)
        {
            SetActorAssetRecord(pActor, g_apRoomSwitchAssetRecords[pActor->wCharacterId_candidate]);

            if ((pActor->wCharacterId_candidate == 9 || pActor->wCharacterId_candidate == 10) && pRecord->bInitialFrame != 0)
                SetActorAnimFrame(pActor, 1);
            else
                SetActorAnimFrame(pActor, 0);

            if (g_bRestoringRoomActors_candidate == 0)
                pActor->bActionFlags = 0;
            else
                pActor->bActionFlags |= 0x20;

            pActor->apfnCollisionCallback[0] = HandleSwitchActorTouch;
            pActor->dwFlags |= ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagUnk2000;
            pActor->dwFlags &= ~ActorFlagTickHandlerSuspendsMovement;
        }
    }

    return pActor;
}
