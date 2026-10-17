#include "types.h"
#include "color.h"
#include "modes.h"
#include "actor.h"
#include "pscreen_folio_bruti.h"
#include "screen_transitions.h"

void ExitFolioBruti(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllActors(&g_ActiveActorListState.pHead);

    g_FolioBrutiState.pMonster = NULL;
    g_FolioBrutiState.pCursor = NULL;
    for (i = 0; i < ARRAY_COUNT(g_FolioBrutiState.apSpellDots); i++)
        g_FolioBrutiState.apSpellDots[i] = NULL;

    ClearMonsterDexNewFlags();

    if (g_PrevGameModeStackContext.dwCurrentGameMode == Battle)
        g_GameModeStackContext.dwCurrentGameMode = FolioUniversitas;
}
