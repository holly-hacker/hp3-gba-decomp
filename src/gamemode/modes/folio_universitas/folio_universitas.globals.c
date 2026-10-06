#include "types.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"
#include "gen/graphics/overworld.h"

const u32 g_dwFolioUniversitasBg3Control = 0x3F03;
const u32 g_dwFolioUniversitasBg1Control = 0x3E0A;
const u32 g_dwFolioUniversitasBg0Control = 0x1D05;

#define OBJECT_GFX(name) { (void *)g##name##Tiles, (void *)g##name##Frames }

const ObjectGfxRecord g_aFolioUniversitasObjectGfx[6] = {
    OBJECT_GFX(FolioUniversitasCursor),
    OBJECT_GFX(ButtonPrompts),
    OBJECT_GFX(ObjectSprite030),
    OBJECT_GFX(ObjectSprite031),
    OBJECT_GFX(ObjectSprite032),
    OBJECT_GFX(FolioUniversitasCountBadges),
};
