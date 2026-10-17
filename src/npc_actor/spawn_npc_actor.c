#include "types.h"
#include "area.h"
#include "npc_actor.h"

// Room actor constructor for tile actorType 6, an NPC; see docs/formats/rooms.md.
// bFighterIndex doubles as the kind index into the asset tables.
Actor *SpawnNpcActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordUnk6 *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(pRecord->dwActorType);

    SetActorPosition(pActor, pRecord->nPixelX, pRecord->nPixelY);
    pActor->dwFlags = 0x04102015;
    pActor->anim.bAnimFrameDelay = 0;
    pActor->bFighterIndex = pRecord->bKind;
    pActor->bRoomActorKind_candidate = pRecord->argC.bFirst;

    if ((pRecord->argC.dwWord & 0x00FFFF00) == 0)
        pActor->bFlags_0x94_candidate |= 3;

    pActor->pfnTick = sub_0802F7F0;
    pActor->apfnCollisionCallback[0] = sub_0802FCC0;
    pActor->apfnCollisionCallback[1] = 0;
    SetActorPendingPalette(pActor, g_aActorTypeAssets[pActor->bFighterIndex].pPalette);
    pActor->bFacing = pRecord->bFacing >> 1;
    SetActorAssetRecord(pActor, &g_aActorTypeAssets[pActor->bFighterIndex]);
    SetActorAnimFrame(pActor, g_abRoomActorUnk6Frames[g_adwRoomActorUnk6FrameRows[pActor->bFighterIndex]][pActor->bFacing]);
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0x80;
    pActor->nMoveSpeed = 0x10000;
    SetActorPrevActionState(pActor, 0);
    SetActorActionState(pActor, 0);
    pActor->wUnk84 = 0;

    if (pActor->bFighterIndex == 0x21)
        pActor->dwFlags &= ~0x100000;

    if (pActor->bFighterIndex == 0x5F)
    {
        pActor->dwFlags &= ~0x100000;
        pActor->oam.priority = 1;
        pActor->bDepthSortBias = 0xFF;
    }
    else
    {
        pActor->pLinkedActor_candidate = sub_0802FD5C(pActor);
    }

    if (pActor->bFighterIndex != 0x5F)
        pActor->oam.hFlip = pActor->bFacing == 3;

    pActor->bFlags_0x94_candidate &= ~4;

    if ((u8)(pActor->bFighterIndex - 0x69) <= 1)
        SetActorAffineTransform(pActor, 0x1C000, 0x1C000, 0, 3);

    if (pActor->bFighterIndex == 5)
        pActor->dwFlags &= ~4;

    return pActor;
}
