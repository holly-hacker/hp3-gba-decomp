#include "initials.h"

void ClearHighScoreNameEntryTail(void)
{
    s32 i;

    // Clears past the entered characters, sparing the slot B-key deletion already cleared.
    for (i = g_HighScoreNameEntry.dwNameLength + 1; i <= HIGH_SCORE_NAME_LENGTH; i++)
        g_HighScoreNameEntry.abName[i] = 0;
}
