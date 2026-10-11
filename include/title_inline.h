#pragma once

#include "types.h"
#include "font.h"
#include "text.h"
#include "title.h"

// The ROM compiles DrawMainMenuEntry into MoveMainMenuCursor and also
// keeps an out-of-line copy, as one translation unit with an inline definition
// would. The file that emits the out-of-line copy defines the linkage macro as
// empty.
#ifndef DRAW_MAIN_MENU_ENTRY_LINKAGE
#define DRAW_MAIN_MENU_ENTRY_LINKAGE extern inline
#endif

// Draws one entry's label, highlighted when it is the selected entry.
DRAW_MAIN_MENU_ENTRY_LINKAGE void DrawMainMenuEntry(u32 entry, u32 selectedEntry)
{
    u32 slot;
    u32 color;

    // Load Game's row is skipped when it is unavailable.
    slot = entry;
    if (!g_MainMenuState.dwLoadGameAvailable && slot > 1)
        slot--;

    color = 0;
    if (entry == selectedEntry)
        color = 6;

    SetTextTargetFromBgControl(g_dwMainMenuBg1Control);
    SelectTextFont(2, color, -1);
    // Labels by MainMenuEntry: "New Game", "Load Game", "Options", "Mini-Games".
    DrawStringAligned(slot * 0x30 + 0x118, 0x20, slot * 0xC + 0x58, GetDialogText(entry + 0x8CD), 0);
}
