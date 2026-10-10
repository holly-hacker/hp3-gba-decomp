#include "types.h"
#include "game/game_modes.h"
#include "input.h"
#include "minigame/high_score_name_entry.h"

void UpdateHighScoreNameEntry(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (g_wKeysPressed & KeyA)
    {
        if (g_HighScoreNameEntry.dwNameLength <= 2 && g_HighScoreNameEntry.dwRow <= 5
            && g_HighScoreNameEntry.dwColumn <= 5)
        {
            g_HighScoreNameEntry.abName[g_HighScoreNameEntry.dwNameLength] = g_HighScoreNameEntry.abCandidate[0];
            g_HighScoreNameEntry.dwNameLength++;
        }

        if (g_HighScoreNameEntry.dwRow == 6 && g_HighScoreNameEntry.dwColumn != 4
            && g_HighScoreNameEntry.dwColumn == 5)
            PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);

        DrawHighScoreNameEntryPreview();
    }
    else if (g_wKeysPressed & KeyB)
    {
        if (g_HighScoreNameEntry.dwNameLength > 0)
            g_HighScoreNameEntry.dwNameLength--;

        g_HighScoreNameEntry.abName[g_HighScoreNameEntry.dwNameLength] = 0;
        DrawHighScoreNameEntryPreview();
    }
}
