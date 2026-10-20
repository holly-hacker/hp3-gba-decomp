#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "save.h"
#include "minigame_difficulty_select.h"

void DrawMinigameDifficultyHighScore(s32 row)
{
    const u8 *text;
    u32 score;
    s32 width;
    u32 halfTiles;

    if (g_dwSelectedMinigame <= 2 && row <= MINIGAME_DIFFICULTY_COUNT - 1
        && (score = g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][row]) != 0)
    {
        SelectTextFont(4, 1, 0);
        SetTextMacro1Number(score);
        text = GetDialogText(0x8D1);  // "High Score: @1"
        width = MeasureMacroString(text);
        halfTiles = width / 8;
        halfTiles /= 2;

        // Clear either side of the centered text.
        ClearBgTilemapRect(2, halfTiles + 16, 12, 15 - halfTiles, 2);
        ClearBgTilemapRect(2, 0, 12, 15 - halfTiles, 2);
        DrawTextLines(0x160, 0x7C, 0x60, 0xD0, 0x10, &text, 1);
    }
    else
    {
        ClearBgTilemapRect(2, 0, 12, 30, 2);
    }
}
