#include "types.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"

Object *SpawnFolioCardObject(u32 cardIndex, s32 x, s32 y)
{
    Object *pObject = SpawnObject(0, x, y, 0);

    pObject->oam.bpp8 = 1;
    sub_0800D264(g_aFolioCardAssets[cardIndex].asset.pPalette, 0, 0x100);
    SetObjectAssetRecord(pObject, &g_aFolioCardAssets[cardIndex].asset);
    return pObject;
}
