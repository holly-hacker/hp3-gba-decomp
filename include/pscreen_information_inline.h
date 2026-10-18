#pragma once

#include "font.h"
#include "text.h"
#include "pscreen_information.h"

// The ROM compiles DrawHelpMenuEntry into SetHelpMenuSelection and also keeps an
// out-of-line copy, as one translation unit with an inline definition would. The
// file that emits the out-of-line copy defines the linkage macro as empty.
#ifndef DRAW_HELP_MENU_ENTRY_LINKAGE
#define DRAW_HELP_MENU_ENTRY_LINKAGE extern inline
#endif

DRAW_HELP_MENU_ENTRY_LINKAGE void DrawHelpMenuEntry(u32 entry, u32 color)
{
    const u8 *text;

    if (g_HelpState.aEntries[entry].bAvailable)
        SelectTextFont(2, color, -1);
    else
        SelectTextFont(1, 1, -1);
    text = GetDialogText(g_HelpState.aEntries[entry].dwTextId);
    DrawTextLines(entry * 40 + 0x20, 0x1A, entry * HELP_MENU_ROW_HEIGHT + 0x20, HELP_MENU_ROW_WIDTH,
                  HELP_MENU_ROW_HEIGHT, &text, 0);
}
