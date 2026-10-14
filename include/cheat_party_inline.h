#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "cheat_party.h"

// The ROM inlines this into DrawCheatPartyRows and also keeps an out-of-line copy;
// the file that emits that copy defines the linkage macro as empty.
#ifndef DRAW_CHEAT_PARTY_CHARACTERS_LINKAGE
#define DRAW_CHEAT_PARTY_CHARACTERS_LINKAGE extern inline
#endif

DRAW_CHEAT_PARTY_CHARACTERS_LINKAGE void DrawCheatPartyCharacters(void)
{
    u32 tileCursor;
    const u8 *text;
    s32 i;
    s32 y;

    tileCursor = g_CheatPartyState.dwTileCursor;
    FillBgTilemapRect(1, 0x12, 4, 0xC, 0xC, 0);
    SelectTextFont(9, 0, -1);
    for (i = 0, y = 0x32; i < 3; y += 0x12, i++)
    {
        u32 character = g_CheatPartyState.adwCharacter[i];

        if (character - 1 <= 8)
            text = sPlayableCharacterNames[character - 1];
        else
            text = GetDialogText(0x526);  // "None"
        tileCursor = PrintTextBox(tileCursor + 1, 0xC4, y, 0x64, text, 1);
    }
}
