#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "font.h"
#include "game_state.h"
#include "gen/graphics/battle.h"
#include "save.h"
#include "text.h"

// Draws the active enemy's panel in panelSlot: portrait, HP bar, "SP" label, HP/max HP
// and level. The HP figures read "??" until the monster is documented in Folio Bruti.
void DrawEnemyStatsUi(u8 fighterIndex, u8 panelSlot)
{
    BattleFighter *pEnemy = &g_pFightState->pFighters[fighterIndex];
    const u16 *pTilemap;
    const u8 *text;
    u16 barRow;

    g_pFightState->dwStatsTextTileCursor = 0x60;
    ShowEnemyStatsPortrait(pEnemy->bRosterIndex);
    pTilemap = GetGraphicBlobTilemap(1, gBattleHudPanel);
    CopyBgTilemapRect(0, pTilemap, 1, 0, panelSlot * 10 + 4, 0, panelSlot * 10 + 4, 24, 6, 6);

    if (pEnemy->stats.wHp == 0 || g_saveStateBlock.abMonsterDocLevel[pEnemy->bRosterIndex] == 0)
    {
        CopyBgTilemapRect(0, pTilemap, 1, 0, 26, 6, panelSlot * 10 + 6, 27, 4, 1);
    }
    else
    {
        barRow = 25 - pEnemy->stats.wHp * 25 / pEnemy->wHp_max;
        CopyBgTilemapRect(0, pTilemap, 1, 0, 0, barRow + 6, panelSlot * 10 + 6, 27, 4, 1);
    }

    SelectTextFont(8, 0, -1);
    text = GetDialogText(0x8EA);  // "SP"
    g_pFightState->dwStatsTextTileCursor =
        DrawString(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 39, 208, text);

    if (g_saveStateBlock.abMonsterDocLevel[pEnemy->bRosterIndex] == 0)
        text = GetDialogText(0x905);  // "??"
    else
        text = FormatDecimal(pEnemy->stats.wHp, (u8 *)text);
    SetTextMacro1String(text);

    if (g_saveStateBlock.abMonsterDocLevel[pEnemy->bRosterIndex] == 0)
        text = GetDialogText(0x905);  // "??"
    else
        text = FormatDecimal(pEnemy->wHp_max, (u8 *)text);
    SetTextMacro2String(text);

    text = GetDialogText(0x8EF);  // "@1/@2"
    g_pFightState->dwStatsTextTileCursor =
        DrawTextLines(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 80, 208, 96,
                      BATTLE_STATS_LINE_HEIGHT, &text, 2);

    SetTextMacro1Number(pEnemy->stats.bLevel);
    SetTextMacro2String(g_sBattleTextSpace);
    text = GetDialogText(0x685);  // "Level: @1 @2"
    g_pFightState->dwStatsTextTileCursor =
        DrawTextLines(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 39, 200, 96,
                      BATTLE_STATS_LINE_HEIGHT, &text, 0);
}
