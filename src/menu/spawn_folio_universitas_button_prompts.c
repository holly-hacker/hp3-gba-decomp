#include "types.h"
#include "gen/graphics/overworld.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"

void SpawnFolioUniversitasButtonPrompts(void)
{
    const ObjPalette *pPalette = (const ObjPalette *)gObjectSprite087Palette;

    g_FolioUniversitasState.pPrevArrow = SpawnObject(0, 0x10, 0x98, pPalette);
    SetObjectAnimData(g_FolioUniversitasState.pPrevArrow, FOLIO_UNIVERSITAS_PROMPTS_GFX, g_aFolioButtonPromptAnims[0], 0);
    g_FolioUniversitasState.pPrevArrow->oam.priority = 1;

    g_FolioUniversitasState.pNextArrow = SpawnObject(0, 0x78, 0x98, pPalette);
    SetObjectAnimData(g_FolioUniversitasState.pNextArrow, FOLIO_UNIVERSITAS_PROMPTS_GFX, g_aFolioButtonPromptAnims[1], 0);
    g_FolioUniversitasState.pNextArrow->oam.priority = 1;
}
