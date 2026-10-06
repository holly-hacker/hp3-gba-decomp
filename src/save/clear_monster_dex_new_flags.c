#include "types.h"
#include "game/save.h"
#include "menu/folio_bruti.h"

// Seeing a monster for the first time stores level 2 and analyzing it level 4; the even values mean
// "new" and drop to 1 and 3 once the Folio Bruti has been opened.
void ClearMonsterDexNewFlags(void)
{
    u32 monster;

    for (monster = 0; monster < ARRAY_COUNT(g_saveStateBlock.abMonsterDocLevel); monster++)
    {
        u8 *pLevel = &g_saveStateBlock.abMonsterDocLevel[monster];

        if (*pLevel == 2 || *pLevel == 4)
            (*pLevel)--;
    }
}
