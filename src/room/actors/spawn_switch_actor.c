#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_actor.h"

// Room actor constructor for tile actorType 3, a two-state switch (button,
// pressure plate or lever). See docs/formats/rooms.md.
Actor *SpawnSwitchActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk3 *pRecord = sub_08005C38(bColumn, bRow);
    Actor *pActor = AllocDefaultActor();

    if (pActor != 0)
    {
        SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
        pActor->wActorType = pRecord->dwActorType;
        pActor->dwFlags = 0x808;
        pActor->wCharacterId_candidate = pRecord->bVariant;
        pActor->oam.objMode = 0;
        pActor->oam.bpp8 = 0;
        pActor->oam.priority = 3;
        SetActorPendingPalette(pActor, g_apRoomSwitchEffectData[pActor->wCharacterId_candidate]);
        pActor->bActionState = 0;
        ROOM_ACTOR_WORD_STATE(pActor)->b6D = 0;
        ROOM_ACTOR_WORD_STATE(pActor)->b6C = 1;
        ROOM_ACTOR_WORD_STATE(pActor)->b6F = pRecord->bArgD;
        ROOM_ACTOR_WORD_STATE(pActor)->n60 = pRecord->wArgA * 30;
        pActor->pfnTick = sub_08044D24;

        if (pActor->wCharacterId_candidate <= 10)
        {
            SetActorAssetRecord(pActor, g_apRoomSwitchAssetRecords[pActor->wCharacterId_candidate]);

            if ((pActor->wCharacterId_candidate == 9 || pActor->wCharacterId_candidate == 10) && pRecord->bFlagC != 0)
                SetActorAnimFrame(pActor, 1);
            else
                SetActorAnimFrame(pActor, 0);

            if (g_bRestoringRoomActors_candidate == 0)
                pActor->bActionFlags = 0;
            else
                pActor->bActionFlags |= 0x20;

            pActor->apfnCollisionCallback[0] = sub_08044F54;
            pActor->dwFlags |= 0x2005;
            pActor->dwFlags &= ~0x800;
        }
    }

    return pActor;
}
