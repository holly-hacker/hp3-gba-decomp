#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "hw/mem.h"
#include "menu/folio_bruti.h"

void ExitFolioBruti(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllObjects(&g_ActiveObjectListState.pHead);

    g_FolioBrutiState.pMonster = NULL;
    g_FolioBrutiState.pCursor = NULL;
    for (i = 0; i < ARRAY_COUNT(g_FolioBrutiState.apSpellDots); i++)
        g_FolioBrutiState.apSpellDots[i] = NULL;

    ClearMonsterDexNewFlags();

    if (g_PrevGameModeStackContext.dwCurrentGameMode == Battle)
        g_GameModeStackContext.dwCurrentGameMode = FolioUniversitas;
}
