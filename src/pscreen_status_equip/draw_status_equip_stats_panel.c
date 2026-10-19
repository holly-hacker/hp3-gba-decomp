#include "types.h"
#include "font.h"
#include "text.h"
#include "combat.h"
#include "combat_fighter.h"
#include "game_state.h"
#include "default_menu.h"
#include "pscreen_character.h"
#include "pscreen_status_equip.h"

#define FIGHTER g_aPartyMasterStats[g_dwStatusEquipCharacter]

#ifdef VERSION_JP
#define STATS_ROW_HEIGHT 9
#else
#define STATS_ROW_HEIGHT 8
#endif
#define STATS_ROW_Y(row) ((row) * STATS_ROW_HEIGHT + 0x20)

void DrawStatusEquipStatsPanel(void)
{
    const u8 *text;
    s32 i;
    s32 xpToNextLevel;
    s32 y;
    u32 tileCursor;

    BeginMenuScreen(0xA41, 9, 1);  // "Status/Equip"
    DrawStatusEquipSlotName();
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(2, 0, -1);

    // "Level:" through "Magic Def:", with a gap before the Stamina and Defense groups. A
    // character at displayed level 100 has no "Next Level:" row.
    for (i = 0; i <= 8; i++)
    {
        if (i == 2 && FIGHTER.stats.bLevel == 99)
            continue;

        text = GetDialogText(0x594 + i);
        tileCursor = i * 14 + 0x61;
        if (i > 5)
            y = STATS_ROW_Y(i + 2);
        else if (i > 3)
            y = STATS_ROW_Y(i + 1);
        else
            y = STATS_ROW_Y(i);
        DrawTextLines(tileCursor, 0x10, y, 0x60, STATS_ROW_HEIGHT, &text, 0);
    }

    xpToNextLevel = GetPartyMemberXpToNextLevel(g_dwStatusEquipCharacter);

    SetTextMacro1Number(FIGHTER.stats.bLevel + 1);
    text = GetDialogText(0x8F7);  // "@1"
    DrawTextLines(0xED, 0x70, STATS_ROW_Y(0), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(GetPartyMemberTotalXp(g_dwStatusEquipCharacter));
    text = GetDialogText(0x8F7);
    DrawTextLines(0xF9, 0x70, STATS_ROW_Y(1), 0x60, STATS_ROW_HEIGHT, &text, 2);

    if (FIGHTER.stats.bLevel != 99)
    {
        SetTextMacro1Number(xpToNextLevel);
        text = GetDialogText(0x8F7);
        DrawTextLines(0x105, 0x70, STATS_ROW_Y(2), 0x60, STATS_ROW_HEIGHT, &text, 2);
    }

    SetTextMacro1Number(GetSickles());
    text = GetDialogText(0x8F7);
    DrawTextLines(0x111, 0x70, STATS_ROW_Y(3), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(FIGHTER.stats.wHp);
    SetTextMacro2Number(FIGHTER.wHp_max);
    text = GetDialogText(0x8EF);  // "@1/@2"
    DrawTextLines(0x11D, 0x70, STATS_ROW_Y(5), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(FIGHTER.stats.wMp);
    SetTextMacro2Number(FIGHTER.wMp_max);
    text = GetDialogText(0x8EF);
    DrawTextLines(0x129, 0x70, STATS_ROW_Y(6), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(100 - FIGHTER.bDefenseFactorPercent);
    text = GetDialogText(0x8F7);
    DrawTextLines(0x135, 0x70, STATS_ROW_Y(8), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(0xFF - FIGHTER.bAgility);
    text = GetDialogText(0x8F7);
    DrawTextLines(0x141, 0x70, STATS_ROW_Y(9), 0x60, STATS_ROW_HEIGHT, &text, 2);

    SetTextMacro1Number(100 - FIGHTER.bMagicDefensePercent);
    text = GetDialogText(0x8F7);
    DrawTextLines(0x14D, 0x70, STATS_ROW_Y(10), 0x60, STATS_ROW_HEIGHT, &text, 2);
}
