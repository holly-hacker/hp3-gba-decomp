#include "types.h"
#include "char_block.h"
#include "color.h"
#include "mem.h"
#include "actor.h"
#include "pscreen_folio_universitas.h"
#include "screen_transitions.h"

void ExitFolioUniversitas(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeBgTileAnimations();

    g_FolioUniversitasState.pCursor = NULL;
    for (i = 0; i < ARRAY_COUNT(g_FolioUniversitasState.aComboSlots); i++)
    {
        g_FolioUniversitasState.aComboSlots[i].pCard = NULL;
        g_FolioUniversitasState.aComboSlots[i].pCount = NULL;
    }
}
