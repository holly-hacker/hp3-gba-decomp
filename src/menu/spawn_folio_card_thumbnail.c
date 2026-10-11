#include "types.h"
#include "actor.h"
#include "menu/folio_universitas.h"

Actor *SpawnFolioCardThumbnail(u32 cardIndex, s32 x, s32 y)
{
    Actor *pObject = SpawnActor(0x13, x, y, (const ObjPalette *)g_aFolioCardThumbnails[cardIndex].pPalette);

    SetActorAssetRecord(pObject, &g_aFolioCardThumbnails[cardIndex]);
    return pObject;
}
