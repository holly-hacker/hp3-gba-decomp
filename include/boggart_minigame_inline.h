#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "modes.h"
#include "boggart_minigame.h"

// The ROM inlines the HUD and message drawing below into the round handlers and
// also keeps an out-of-line copy of the two HUD functions. The files that emit
// those copies define the linkage macro as empty.
#ifndef DRAW_BOGGART_MINIGAME_SCORE_LINKAGE
#define DRAW_BOGGART_MINIGAME_SCORE_LINKAGE extern inline
#endif
#ifndef DRAW_BOGGART_MINIGAME_LIVES_LINKAGE
#define DRAW_BOGGART_MINIGAME_LIVES_LINKAGE extern inline
#endif

DRAW_BOGGART_MINIGAME_SCORE_LINKAGE void DrawBoggartMinigameScore(void)
{
    const u8 *text;

    ClearBgTilemapRect(3, 0, 0, 10, 4);
    SelectTextFont(5, 0, -1);
    SetTextMacro1Number(g_BoggartMinigame.dwScore);
    text = GetDialogText(0x58A);  // "Score\n@1"
    DrawTextLines(1, 0x28, 2, 0x50, 0x20, &text, 1);
}

DRAW_BOGGART_MINIGAME_LIVES_LINKAGE void DrawBoggartMinigameLives(void)
{
    const u8 *text;

    ClearBgTilemapRect(3, 0x14, 0x10, 10, 4);
    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 2)
        SelectTextFont(5, 0, -1);
    else
        SelectTextFont(5, 0, -1);
    SetTextMacro1Number(g_BoggartMinigame.bLives);
    text = GetDialogText(0x58B);  // "Lives\n@1"
    DrawTextLines(0x41, 0xC8, 0x82, 0x50, 0x20, &text, 1);
}

extern inline void DrawBoggartMinigameMessage(s32 textId)
{
    const u8 *text;

    SelectTextFont(5, 7, -1);
    text = GetDialogText(textId);  // 0x58D "Failed!" or 0x58F "Great!"
    DrawTextLines(0x81, 0x78, 0x48, 0x60, 0x20, &text, 1);
}
