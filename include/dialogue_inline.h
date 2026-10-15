#pragma once

#include "types.h"
#include "background.h"
#include "dialogue.h"

// Clears the box and starts drawing the rest of pText as a new page.
static inline void StartDialogPage(void)
{
    g_DialogState_candidate.wRevealCount = 0;
    g_DialogState_candidate.bTextY = g_dwDialogBoxTileRow * 8 + DIALOG_TEXT_TOP;
    g_DialogState_candidate.wTextHeightLeft = DIALOG_TEXT_HEIGHT;
    g_DialogState_candidate.wTileCursor = DIALOG_TEXT_FIRST_TILE;
    WriteBgGraphicTilemap_candidate(1, g_pDialogBoxTilemap, DIALOG_BOX_FIRST_TILE, 0, 0, g_dwDialogBoxTileRow);
    g_dwDialogPageFull = DrawDialogTextLine(g_DialogState_candidate.wRevealCount);
}
