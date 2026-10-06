#include "types.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"

Object *SpawnFolioCardThumbnail(u32 cardIndex, s32 x, s32 y)
{
    Object *pObject = SpawnObject(0x13, x, y, (const ObjPalette *)g_aFolioCardThumbnails[cardIndex].pPalette);

    SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[cardIndex]);
    return pObject;
}
