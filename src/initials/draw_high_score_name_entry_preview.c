#include "background.h"
#include "font.h"
#include "initials.h"

void DrawHighScoreNameEntryPreview(void)
{
    HighScoreNameEntryState *pState = &g_HighScoreNameEntry;
    u32 tileCursor;

    FillBgTilemapRect(0, 22, 6, 6, 2, 0);
    ClearHighScoreNameEntryTail();
    SelectTextFont(5, 0, -1);
    // Redrawn into the same tiles each time; dwTileCursor is not advanced.
    tileCursor = DrawString(pState->dwTileCursor, 180, 50, pState->abName);
    if (pState->dwNameLength <= 2)
    {
        UpdateHighScoreNameEntrySelectedChar();
        SelectTextFont(5, 2, -1);
        DrawString(tileCursor, MeasureMacroString(pState->abName) + 180, 50, pState->abCandidate);
    }
}
