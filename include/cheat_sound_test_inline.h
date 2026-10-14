#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_sound_test.h"

// The ROM inlines this into DrawCheatSoundTestRows and also keeps an out-of-line copy;
// the file that emits that copy defines the linkage macro as empty.
#ifndef DRAW_CHEAT_SOUND_TEST_VALUES_LINKAGE
#define DRAW_CHEAT_SOUND_TEST_VALUES_LINKAGE extern inline
#endif

DRAW_CHEAT_SOUND_TEST_VALUES_LINKAGE void DrawCheatSoundTestValues(void)
{
    u32 tileCursor;
    u8 *text;
    s32 i;

    tileCursor = g_CheatSoundTestState.dwTileCursor;
    text = GetDialogText(0x8F7);  // "@1 "
    FillBgTilemapRect(1, 0x15, 5, 4, 0xC, 0);
    for (i = 0; i < 2; i++)
    {
        SetTextMacro1Number(g_CheatSoundTestState.adwSelection[i]);
        tileCursor = PrintTextBox(tileCursor + 1, 0xB4, 0x32 + i * 0x12, 0x64, text, 1);
    }
}
