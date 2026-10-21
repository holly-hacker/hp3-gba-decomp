#include "initials.h"

void UpdateHighScoreNameEntrySelectedChar(void)
{
    s32 key;

    if (g_HighScoreNameEntry.dwNameLength <= 2)
    {
        key = g_HighScoreNameEntry.dwRow * HIGH_SCORE_KEYPAD_COLUMNS + g_HighScoreNameEntry.dwColumn;
        if (key <= 25)
            g_HighScoreNameEntry.abCandidate[0] = 'A' + key;
        // Keys 26-35 are the digits; the "Done" row has no character.
        else if (g_HighScoreNameEntry.dwRow <= 5)
            g_HighScoreNameEntry.abCandidate[0] = '0' + key - 26;
        else
            g_HighScoreNameEntry.abCandidate[0] = 0;
    }
    else
    {
        g_HighScoreNameEntry.abCandidate[0] = 0;
    }
}
