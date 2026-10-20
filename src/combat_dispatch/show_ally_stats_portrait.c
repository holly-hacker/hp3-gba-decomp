#include "types.h"
#include "actor.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"

// Shows the party member's face beside the battle stats panel.
void ShowAllyStatsPortrait(u32 fighterType)
{
    SetActorAssetRecord(g_pStatsPortraitActor, &g_aPartyFaceAssets[fighterType]);
    SetActorAnimFrame(g_pStatsPortraitActor, 0);
    QueueStatsPortraitPalette(g_pStatsPortraitActor->oam.paletteNum + 16,
                              g_aPartyFaceAssets[fighterType].pPalette);
    g_pStatsPortraitActor->dwFlags |= ActorFlagVisible;
}
