#include "font.h"
#include "mem.h"
#include "initials.h"

void DrawHighScoreNameEntryKeypad(void)
{
    u8 key[2];
    s32 row;
    s32 column;

    memcpy(key, g_abHighScoreNameEntryKeyTemplate, sizeof(key));
    for (row = 0; row < HIGH_SCORE_KEYPAD_ROWS; row++)
    {
        for (column = 0; column < HIGH_SCORE_KEYPAD_COLUMNS; column++)
        {
            g_HighScoreNameEntry.dwTileCursor = DrawString(g_HighScoreNameEntry.dwTileCursor,
                column * 20 + 20, row * 20 + 20, key);
            // Letters A-Z, then digits from the 27th key.
            if (row * HIGH_SCORE_KEYPAD_COLUMNS + (column + 1) == 26)
                key[0] = '0';
            else
                key[0]++;
        }
    }

    g_HighScoreNameEntry.dwTileCursor = DrawStringAligned(g_HighScoreNameEntry.dwTileCursor,
        (column - 1) * 20 + 20, row * 20 + 20, g_abHighScoreNameEntryDoneText, 1);
}
