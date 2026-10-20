#include "types.h"
#include "actor.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"

// Shows the monster's face beside the battle stats panel.
void ShowEnemyStatsPortrait(u32 monsterId)
{
    QueueStatsPortraitPalette(g_pStatsPortraitActor->oam.paletteNum + 16,
                              g_aMonsterFaceAssets[monsterId].pPalette);
    SetActorAssetRecord(g_pStatsPortraitActor, &g_aMonsterFaceAssets[monsterId]);
    SetActorAnimFrame(g_pStatsPortraitActor, 0);
    g_pStatsPortraitActor->dwFlags |= ActorFlagVisible;
}
