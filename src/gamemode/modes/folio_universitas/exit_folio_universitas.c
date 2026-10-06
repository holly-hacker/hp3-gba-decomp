#include "types.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "hw/mem.h"
#include "menu/folio_universitas.h"

void ExitFolioUniversitas(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800A914();

    g_FolioUniversitasState.pCursor = NULL;
    for (i = 0; i < ARRAY_COUNT(g_FolioUniversitasState.aComboSlots); i++)
    {
        g_FolioUniversitasState.aComboSlots[i].pCard = NULL;
        g_FolioUniversitasState.aComboSlots[i].pCount = NULL;
    }
}
