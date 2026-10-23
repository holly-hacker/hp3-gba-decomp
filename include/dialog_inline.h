#pragma once

#include "background.h"
#include "dialog.h"

// Clears the box and starts drawing the rest of pText as a new page.
static inline void StartDialogPage(void)
{
    g_DialogState.wRevealCount = 0;
    g_DialogState.bTextY = g_dwDialogBoxTileRow * 8 + DIALOG_TEXT_TOP;
    g_DialogState.wTextHeightLeft = DIALOG_TEXT_HEIGHT;
    g_DialogState.wTileCursor = DIALOG_TEXT_FIRST_TILE;
    WriteBgGraphicTilemap(1, g_pDialogBoxTilemap, DIALOG_BOX_FIRST_TILE, 0, 0, g_dwDialogBoxTileRow);
    g_dwDialogPageFull = DrawDialogTextLine(g_DialogState.wRevealCount);
}
