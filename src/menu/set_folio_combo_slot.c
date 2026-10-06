#include "types.h"
#include "game/save.h"
#include "gen/graphics/overworld.h"
#include "graphics/object.h"
#include "menu/folio_universitas.h"

// Shows card `cardIndex` in one of the three combo slots; any index past the last card
// (such as 0x33) leaves the slot empty.
void SetFolioComboSlot(u32 cardIndex, u32 slot)
{
    Object *pObject;

    if (g_FolioUniversitasState.aComboSlots[slot].pCard != NULL)
    {
        g_FolioUniversitasState.aComboSlots[slot].pCard->dwFlags =
            (g_FolioUniversitasState.aComboSlots[slot].pCard->dwFlags & ~ObjectFlagVisible) | 0x82;
        g_FolioUniversitasState.aComboSlots[slot].pCard = NULL;
    }
    if (g_FolioUniversitasState.aComboSlots[slot].pCount != NULL)
    {
        g_FolioUniversitasState.aComboSlots[slot].pCount->dwFlags =
            (g_FolioUniversitasState.aComboSlots[slot].pCount->dwFlags & ~ObjectFlagVisible) | 0x82;
        g_FolioUniversitasState.aComboSlots[slot].pCount = NULL;
    }

    if (cardIndex <= 0x32)
    {
        pObject = SpawnObject(0x13, slot * 40 + 0x78, 0x58,
                              (const ObjPalette *)g_aFolioCardThumbnails[cardIndex].pPalette);
        SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[cardIndex]);
        g_FolioUniversitasState.aComboSlots[slot].pCard = pObject;
        pObject->oam.priority = 1;
        g_FolioUniversitasState.aComboSlots[slot].pCard->oam.objMode = 0;

        g_FolioUniversitasState.aComboSlots[slot].pCount =
            SpawnObject(0, slot * 40 + 0x84, 0x80, (const ObjPalette *)gObjectSprite086Palette);
        SetObjectAssetRecord(g_FolioUniversitasState.aComboSlots[slot].pCount, FOLIO_UNIVERSITAS_BADGES_GFX);
        SetObjectAnimFrame(g_FolioUniversitasState.aComboSlots[slot].pCount,
                           g_saveStateBlock.abFolioUniversitasCounts[cardIndex]);
        g_FolioUniversitasState.aComboSlots[slot].pCount->oam.priority = 1;
        g_FolioUniversitasState.aComboSlots[slot].pCount->oam.objMode = 0;
    }
}
