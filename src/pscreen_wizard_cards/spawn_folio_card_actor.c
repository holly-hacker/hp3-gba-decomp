#include "types.h"
#include "color.h"
#include "actor.h"
#include "pscreen_wizard_cards.h"

Actor *SpawnFolioCardActor(u32 cardIndex, s32 x, s32 y)
{
    Actor *pActor = SpawnActor(0, x, y, 0);

    pActor->oam.bpp8 = 1;
    QueueObjPaletteLoad((const u16 *)g_aFolioCardAssets[cardIndex].asset.pPalette, 0, 0x100);
    SetActorAssetRecord(pActor, &g_aFolioCardAssets[cardIndex].asset);
    return pActor;
}
