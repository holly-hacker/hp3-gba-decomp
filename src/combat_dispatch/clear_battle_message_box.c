#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_dispatch.h"

void ClearBattleMessageBox(void)
{
    s32 row;

    ClearBgTilemapRect(0, 10, 24, 20, 6);
    g_pFightState->dwTextTileCursor = 0xA0;

    for (row = 0; row < 7; row++)
        HideBattleMenuIcon(row);
}
