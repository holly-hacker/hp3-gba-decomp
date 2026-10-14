#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_level_and_quest_inline.h"

void DrawCheatLevelAndQuestRows(void)
{
    u32 tileCursor;
    s32 i;
    s32 y;
    u8 *text;

    tileCursor = 0;
    FillBgTilemapRect(1, 0x15, 5, 4, 0xC, 0);
    for (i = 0, y = 0x32; i < 4; y += 0x12, i++)
    {
        if (i == 3)
            text = GetDialogText(0x536);  // "Current Quest"
        else
            text = GetDialogText(0x907 + i);  // "Harry", "Ron", "Hermione"
        tileCursor = PrintTextBox(tileCursor + 1, 0x50, y, 0x64, text, 1);
    }
    g_CheatLevelAndQuestState.dwTileCursor = tileCursor;

    DrawCheatLevelAndQuestValues();
}
