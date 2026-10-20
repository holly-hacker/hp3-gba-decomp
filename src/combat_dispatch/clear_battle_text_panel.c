#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_dispatch.h"

void ClearBattleTextPanel(void)
{
    s32 row;

    ClearBgTilemapRect(0, 0, 24, 30, 6);
    g_pFightState->dwStatsTextTileCursor = 0x60;
    g_pFightState->dwTextTileCursor = 0xA0;

    for (row = 0; row < 7; row++)
        HideBattleMenuIcon(row);
}
