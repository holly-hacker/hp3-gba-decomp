#include "lupin_potion_cutscene.h"
#include "color.h"
#include "palette.h"

// Kind 0 is a piece of the panel; the others are 8bpp portraits whose colors load into
// OBJ palette 1.
Actor *SpawnLupinPotionPanelActor(s32 kind)
{
    Actor *pActor = AllocActorOfType(RoomActorType_Npc);

    if (pActor != NULL)
    {
        pActor->wSubtype = kind;
        pActor->dwFlags = ActorFlagVisible | ActorFlagHasSpriteCells;
        pActor->oam.objMode = 0;
        if (kind == 0)
        {
            pActor->oam.bpp8 = 0;
            SetActorPendingPalette(pActor, g_aLupinPotionPanelAssets[0].pPalette);
        }
        else
        {
            pActor->oam.bpp8 = 1;
            QueueObjPaletteLoad(g_aLupinPotionPanelAssets[kind].pPalette[1].aColors, 16, 32);
            pActor->oam.paletteNum = 1;
            pActor->pPendingPalette = NULL;
            pActor->dwPendingPaletteFlags = 0;
        }
        SetActorAssetRecord(pActor, &g_aLupinPotionPanelAssets[kind]);
        pActor->oam.priority = 1;
        pActor->bDepthSortBias = 0x80;
    }
    return pActor;
}
