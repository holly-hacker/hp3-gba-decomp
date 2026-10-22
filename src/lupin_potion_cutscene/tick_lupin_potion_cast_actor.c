#include "lupin_potion_cutscene.h"
#include "color.h"
#include "palette.h"
#include "random.h"

// Restarts the cast member's animation when its script changes its velocity, facing or
// pose (bActionFlags 0x2, or 0x10 from SetActorFacing).
void TickLupinPotionCastActor(Actor *pActor)
{
    s8 facing = pActor->bFacing;
    const ActorAssetRecord *pAsset;
    FixedPoint pos;

    if ((pActor->bActionFlags & 0x12) == 0)
        return;

    if (pActor->bActionSubState == 4)
        pAsset = &g_aLupinPotionPose4Assets[g_LupinPotionCutscene.aCastScripts[pActor->bFighterIndex].nArg];
    else if (pActor->bFighterIndex <= 2)
        pAsset = &g_aLupinPotionPoseAssets[pActor->bActionSubState][pActor->bFighterIndex];
    else
        pAsset = &g_aLupinPotionCastAssets[pActor->bFighterIndex];
    ReleaseActorPalette(pActor);
    AttachActorPalette(pActor, pAsset->pPalette);

    switch (pActor->bActionSubState)
    {
    case 0:
    default:
        if (pActor->vel.x == 0 && pActor->vel.y == 0)
        {
            SetActorAssetRecord(pActor, pAsset);
            SetActorAnimFrame(pActor, g_abLupinPotionStandFrames[facing]);
        }
        else if ((pActor->vel.x > 0 && facing == Direction4Left)
                 || (pActor->vel.x < 0 && facing == Direction4Right))
            SetActorAnimDataAtCommand(pActor, pAsset, g_aLupinPotionWalkBackAnims[facing], Mt19937RandMax2(7));
        else
            SetActorAnimDataAtCommand(pActor, pAsset, g_aLupinPotionWalkAnims[facing], Mt19937RandMax2(7));
        break;
    case 4:
        SetActorAnimData(pActor, pAsset,
                         g_aLupinPotionPose4Anims[g_LupinPotionCutscene.aCastScripts[pActor->bFighterIndex].nArg], 0);
        switch (g_LupinPotionCutscene.aCastScripts[pActor->bFighterIndex].nArg)
        {
        case 1:
            pos.x = pActor->pos.x + 0x190000;
            pos.y = pActor->pos.y - 0x130000;
            SpawnLupinPotionEffectActor(0, pos);
            break;
        case 3:
            SpawnLupinPotionEffectActor(1, pActor->pos);
            break;
        }
        break;
    case 2:
        if (pActor->vel.x == 0 && pActor->vel.y == 0)
            SetActorAnimData(pActor, pAsset, g_aLupinPotionPose2StandAnims[pActor->bFighterIndex], 0);
        else
            SetActorAnimData(pActor, pAsset, g_aLupinPotionPose2WalkAnims[pActor->bFighterIndex], 0);
        break;
    case 1:
        SetActorAnimData(pActor, pAsset, g_aLupinPotionPose1Anims[pActor->bFighterIndex], 0);
        switch (pActor->bFighterIndex)
        {
        case 0:
        case 1:
            StartPaletteEffect(pActor->oam.paletteNum << 4, 16, 10, 30, 13,
                               g_aLupinPotionPoseAssets[2][pActor->bFighterIndex].pPalette->aColors);
            break;
        case 2:
            break;
        }
        break;
    }

    pActor->bActionFlags = 0;
    pActor->oam.hFlip = facing > Direction4Down;
}
