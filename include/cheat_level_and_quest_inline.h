#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_level_and_quest.h"

// The ROM inlines this into DrawCheatLevelAndQuestRows and also keeps an
// out-of-line copy; the file that emits that copy defines the linkage macro as empty.
#ifndef DRAW_CHEAT_LEVEL_AND_QUEST_VALUES_LINKAGE
#define DRAW_CHEAT_LEVEL_AND_QUEST_VALUES_LINKAGE extern inline
#endif

DRAW_CHEAT_LEVEL_AND_QUEST_VALUES_LINKAGE void DrawCheatLevelAndQuestValues(void)
{
    u32 tileCursor;
    u8 *text;
    s32 i;
    s32 y;

    tileCursor = g_CheatLevelAndQuestState.dwTileCursor;
    text = GetDialogText(0x8F7);  // "@1 "
    FillBgTilemapRect(1, 0x15, 5, 4, 0xC, 0);
    y = 0x32;
    for (i = 0; i < 4; i++)
    {
        SetTextMacro1Number(g_CheatLevelAndQuestState.adwValue[i]);
        tileCursor = PrintTextBox(tileCursor + 1, 0xB4, y, 0x64, text, 1);
        y += 0x12;
    }
}
