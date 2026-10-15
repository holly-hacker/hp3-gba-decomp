#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "dementor_minigame.h"

// The ROM inlines the HUD drawing below into the gameplay handlers and also
// keeps an out-of-line copy of each. The files that emit those copies define
// the linkage macro as empty.
#ifndef DRAW_DEMENTOR_MINIGAME_SCORE_LINKAGE
#define DRAW_DEMENTOR_MINIGAME_SCORE_LINKAGE extern inline
#endif
#ifndef DRAW_DEMENTOR_MINIGAME_LIVES_LINKAGE
#define DRAW_DEMENTOR_MINIGAME_LIVES_LINKAGE extern inline
#endif
#ifndef DRAW_DEMENTOR_MINIGAME_MISSES_LINKAGE
#define DRAW_DEMENTOR_MINIGAME_MISSES_LINKAGE extern inline
#endif

DRAW_DEMENTOR_MINIGAME_SCORE_LINKAGE void DrawDementorMinigameScore(void)
{
    const u8 *text;

    ClearBgTilemapRect(3, 0, 2, 10, 2);
    SelectTextFont(5, 0, -1);
    SetTextMacro1Number(g_DementorMinigame.dwScore);
    text = GetDialogText(0x58A);  // "Score\n@1"
    DrawTextLines(1, 0x28, 2, 0x60, 0x20, &text, 1);
}

DRAW_DEMENTOR_MINIGAME_LIVES_LINKAGE void DrawDementorMinigameLives(void)
{
    const u8 *text;

    ClearBgTilemapRect(3, 0x13, 0x12, 10, 2);
    SelectTextFont(5, 0, -1);
    SetTextMacro1Number(g_DementorMinigame.bLives);
    text = GetDialogText(0x58B);  // "Lives\n@1"
    DrawTextLines(0x41, 0xC8, 0x82, 0x60, 0x20, &text, 1);
}

// Macro 2 holds the misses that cost a life, which the English text omits.
DRAW_DEMENTOR_MINIGAME_MISSES_LINKAGE void DrawDementorMinigameMisses(void)
{
    const u8 *text;

    ClearBgTilemapRect(3, 0, 0x12, 10, 2);
    SelectTextFont(5, 0, -1);
    SetTextMacro1Number(g_DementorMinigame.bMisses);
    SetTextMacro2Number(3);
    text = GetDialogText(0x590);  // "Spells missed\n@1"
    DrawTextLines(0x81, 0x30, 0x82, 0x60, 0x20, &text, 1);
}
