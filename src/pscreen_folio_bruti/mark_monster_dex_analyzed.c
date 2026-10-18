#include "types.h"
#include "pscreen_folio_bruti.h"
#include "game_state.h"

void MarkMonsterDexAnalyzed(u32 monster)
{
    if (g_saveStateBlock.abMonsterDocLevel[monster] <= 2)
        g_saveStateBlock.abMonsterDocLevel[monster] = 4;
}
