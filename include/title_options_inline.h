#pragma once

#include "types.h"
#include "font.h"
#include "text.h"
#include "title_options.h"

// The ROM compiles DrawOptionsRowLabel into MoveOptionsCursor and also keeps an
// out-of-line copy, as one translation unit with an inline definition would. The
// file that emits the out-of-line copy defines the linkage macro as empty.
#ifndef DRAW_OPTIONS_ROW_LABEL_LINKAGE
#define DRAW_OPTIONS_ROW_LABEL_LINKAGE extern inline
#endif

// Draws a row's label, highlighted when it is the selected row.
DRAW_OPTIONS_ROW_LABEL_LINKAGE void DrawOptionsRowLabel(u32 row, u32 selectedRow)
{
    u32 color;
    const u8 *pText;

    color = 1;
    if (row == selectedRow)
        color = 6;

    SelectTextFont(4, color, 0);
    // Labels by OptionsRow: "Sound", "Music", "Gamma", "Language".
    pText = GetDialogText(row + 0x8D9);
    DrawTextLines(row * 32 + 0x40, g_aOptionsMenuItems[row].nX + 26, g_aOptionsMenuItems[row].nY,
                  0x70, 0x10, &pText, 0);
}
