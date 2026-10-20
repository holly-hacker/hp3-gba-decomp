#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "save.h"
#include "minigame_difficulty_select.h"

void DrawMinigameDifficultyRow(s32 row, u32 fontColor)
{
    const u8 *text;
    u32 align = 0;
    u32 visible = 1;
    u32 tileCursor;
    s32 x;
    s32 y;

    SelectTextFont(4, fontColor, -1);
    text = GetDialogText(g_adwMinigameDifficultyTextIds[row]);

    // "Erase High Scores" is centered and only shown once a score is saved.
    if (row > MINIGAME_DIFFICULTY_COUNT - 1)
    {
        align = 1;
        visible = g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][0] != 0
               || g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][1] != 0
               || g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][2] != 0;
    }

    if (visible)
    {
        tileCursor = row * 64 + 0x60;
        x = 0x7C;
        if (row <= MINIGAME_DIFFICULTY_COUNT - 1)
        {
            x = 0x68;
            y = row * 16 + 0x28;
        }
        else
        {
            y = row * 16 + 0x40;
        }
        DrawTextLines(tileCursor, x, y, 0xA0, 0x10, &text, align);
    }
    else
    {
        ClearBgTilemapRect(2, 0, row <= MINIGAME_DIFFICULTY_COUNT - 1 ? row * 2 + 5 : row * 2 + 8, 0x1E, 2);
    }
}
