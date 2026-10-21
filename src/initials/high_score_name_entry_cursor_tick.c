#include "modes.h"
#include "input.h"
#include "initials.h"

void HighScoreNameEntryCursorTick(Actor *pActor)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown((u32 *)&g_HighScoreNameEntry.dwRow, 0, HIGH_SCORE_KEYPAD_ROWS, 1, 0)
        || StepCursorLeftRight((u32 *)&g_HighScoreNameEntry.dwColumn, 0, HIGH_SCORE_KEYPAD_COLUMNS - 1, 1, 0))
    {
        if (g_HighScoreNameEntry.dwRow == HIGH_SCORE_KEYPAD_ROWS)
            g_HighScoreNameEntry.dwColumn = 5;

        DrawHighScoreNameEntryPreview();
        SetActorMoveTargetWithDuration(pActor, g_HighScoreNameEntry.dwColumn * 20 + 25,
            g_HighScoreNameEntry.dwRow * 20 + 32, 5);
    }
}
