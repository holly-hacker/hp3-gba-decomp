#include "actor.h"
#include "color.h"
#include "pscreen_status_equip.h"

Actor *SpawnStatusCharacterActor(u32 character)
{
    Actor *pActor = AllocActorOfType(1);

    SetActorPosition(pActor, 0x87, 0x12);
    pActor->dwFlags = ActorFlagHasSpriteCells | ActorFlagHasAnimation | ActorFlagHasTickLogic;
    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = NULL;
    pActor->oam.objMode = 0;
    pActor->oam.paletteNum = 14;
    pActor->oam.bpp8 = 1;
    pActor->oam.priority = 2;
    pActor->bDepthSortBias = 0x80;
    QueueObjPaletteLoadAtOffset((const u8 *)g_aStatusCharacterAssets[character].pPalette, pActor->oam.paletteNum * 32,
                                pActor->oam.paletteNum * 16, 0x20);
    SetActorAnimData(pActor, &g_aStatusCharacterAssets[character], g_abStatusCharacterSpinAnim, 0);
    SetActorAnimFrame(pActor, 0);
    pActor->dwFlags |= ActorFlagVisible;
    return pActor;
}
