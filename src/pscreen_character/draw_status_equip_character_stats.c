#include "pscreen_character.h"
#include "combat.h"
#include "combat_fighter.h"
#include "font.h"
#include "text.h"

// Y of each stat row; the Japanese font's rows are a pixel taller.
#ifdef VERSION_JP
#define STAT_ROW_Y(row) (0x62 + (row) * 9)
#else
#define STAT_ROW_Y(row) (0x64 + (row) * 8)
#endif

void DrawStatusEquipCharacterStats(u32 slot, u32 color)
{
    u8 column;
    u8 character;
    u32 tileCursor;
    u8 *text;

    column = StatusEquipSlotToColumn(slot);
    character = StatusEquipSlotToCharacter(slot);
    SelectTextFont(0, 0, -1);

    text = GetDialogText(0x585);  // "Level:"
    tileCursor = DrawString(column * 96 + 0x61, column * 72 + 20, STAT_ROW_Y(0), text);
    SetTextMacro1Number(g_aPartyMasterStats[character].bLevel + 1);
    text = GetDialogText(0x8F7);  // "@1"
    tileCursor = DrawStringAligned(tileCursor, column * 72 + 74, STAT_ROW_Y(0), text, 2);

    text = GetDialogText(0x583);  // "Exp:"
    tileCursor = DrawString(tileCursor, column * 72 + 20, STAT_ROW_Y(1), text);
    SetTextMacro1Number(GetPartyMemberTotalXp(character));
    text = GetDialogText(0x8F7);
    tileCursor = DrawStringAligned(tileCursor, column * 72 + 74, STAT_ROW_Y(1), text, 2);

    if (g_aPartyMasterStats[character].bLevel < 99)
    {
        text = GetDialogText(0x581);  // "Next:"
        tileCursor = DrawString(tileCursor, column * 72 + 20, STAT_ROW_Y(2), text);
        SetTextMacro1Number(GetPartyMemberXpToNextLevel(character));
        text = GetDialogText(0x8F7);
        tileCursor = DrawStringAligned(tileCursor, column * 72 + 74, STAT_ROW_Y(2), text, 2);
    }

    text = GetDialogText(0x582);  // "SP:"
    tileCursor = DrawString(tileCursor, column * 72 + 20, STAT_ROW_Y(3), text);
    SetTextMacro1Number(g_aPartyMasterStats[character].wHp);
    SetTextMacro2Number(g_aPartyMasterStats[character].wHp_max);
    text = GetDialogText(0x8EF);  // "@1/@2"
    tileCursor = DrawStringAligned(tileCursor, column * 72 + 74, STAT_ROW_Y(3), text, 2);

    text = GetDialogText(0x584);  // "MP:"
    tileCursor = DrawString(tileCursor, column * 72 + 20, STAT_ROW_Y(4), text);
    SetTextMacro1Number(g_aPartyMasterStats[character].wMp);
    SetTextMacro2Number(g_aPartyMasterStats[character].wMp_max);
    text = GetDialogText(0x8EF);
    DrawStringAligned(tileCursor, column * 72 + 74, STAT_ROW_Y(4), text, 2);
}
