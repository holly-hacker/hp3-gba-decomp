#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "font.h"
#include "gen/graphics/battle.h"
#include "text.h"

// Draws a party member's panel in panelSlot from its master record: portrait, HP and MP
// bars, "SP"/"MP" labels with current/max values, and level.
void DrawFighterStatsUi(u8 fighterType, u8 panelSlot)
{
    const u16 *pTilemap;
    const u8 *text;
    u16 barRow;

    g_pFightState->dwStatsTextTileCursor = 0x60;
    pTilemap = GetGraphicBlobTilemap(1, gBattleHudPanel);
    CopyBgTilemapRect(0, pTilemap, 1, 0, panelSlot * 10 + 4, 0, panelSlot * 10 + 4, 24, 6, 6);
    ShowAllyStatsPortrait(fighterType);

    if (g_aPartyMasterStats[fighterType].stats.wHp == 0)
    {
        CopyBgTilemapRect(0, pTilemap, 1, 0, 26, 6, panelSlot * 10 + 6, 27, 4, 1);
    }
    else
    {
        barRow = 25 - g_aPartyMasterStats[fighterType].stats.wHp * 25
                          / g_aPartyMasterStats[fighterType].wHp_max;
        CopyBgTilemapRect(0, pTilemap, 1, 0, 0, barRow + 6, panelSlot * 10 + 6, 27, 4, 1);
    }

    if (g_aPartyMasterStats[fighterType].stats.wMp == 0)
    {
        CopyBgTilemapRect(0, pTilemap, 1, 0, 26, 6, panelSlot * 10 + 6, 29, 4, 1);
    }
    else
    {
        barRow = 25 - g_aPartyMasterStats[fighterType].stats.wMp * 25
                          / g_aPartyMasterStats[fighterType].wMp_max;
        CopyBgTilemapRect(0, pTilemap, 1, 0, 22, barRow + 6, panelSlot * 10 + 6, 29, 4, 1);
    }

    SelectTextFont(8, 0, -1);
    text = GetDialogText(0x8EA);  // "SP"
    g_pFightState->dwStatsTextTileCursor =
        DrawString(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 39, 208, text);
    text = GetDialogText(0x8EB);  // "MP"
    g_pFightState->dwStatsTextTileCursor =
        DrawString(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 39, 224, text);

    text = FormatDecimal(g_aPartyMasterStats[fighterType].stats.wHp, (u8 *)text);
    SetTextMacro1String(text);
    text = FormatDecimal(g_aPartyMasterStats[fighterType].wHp_max, (u8 *)text);
    SetTextMacro2String(text);
    text = GetDialogText(0x8EF);  // "@1/@2"
    g_pFightState->dwStatsTextTileCursor =
        DrawTextLines(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 80, 208, 96,
                      BATTLE_STATS_LINE_HEIGHT, &text, 2);

    text = FormatDecimal(g_aPartyMasterStats[fighterType].stats.wMp, (u8 *)text);
    SetTextMacro1String(text);
    text = FormatDecimal(g_aPartyMasterStats[fighterType].wMp_max, (u8 *)text);
    SetTextMacro2String(text);
    text = GetDialogText(0x8EF);  // "@1/@2"
    g_pFightState->dwStatsTextTileCursor =
        DrawTextLines(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 80, 224, 96,
                      BATTLE_STATS_LINE_HEIGHT, &text, 2);

    SetTextMacro1Number(g_aPartyMasterStats[fighterType].stats.bLevel + 1);
    SetTextMacro2String(g_sBattleTextSpace);
    text = GetDialogText(0x685);  // "Level: @1 @2"
    g_pFightState->dwStatsTextTileCursor =
        DrawTextLines(g_pFightState->dwStatsTextTileCursor, panelSlot * 80 + 39, 200, 96,
                      BATTLE_STATS_LINE_HEIGHT, &text, 0);
}
