#include "types.h"
#include "pscreen_folio_bruti.h"
#include "game_state.h"

void MarkMonsterDexSeen(u32 monster)
{
    if (g_saveStateBlock.abMonsterDocLevel[monster] == 0)
        g_saveStateBlock.abMonsterDocLevel[monster] = 2;
}
