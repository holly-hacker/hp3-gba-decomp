#pragma once

#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_gamecube.h"

// The ROM compiles this into UpdateGameCubeLinkStatusText and also keeps an out-of-line copy, as
// one translation unit with an inline definition would. The file that emits the out-of-line copy
// defines the linkage macro as empty.
#ifndef SHOW_GAMECUBE_LINK_MESSAGE_LINKAGE
#define SHOW_GAMECUBE_LINK_MESSAGE_LINKAGE extern inline
#endif

SHOW_GAMECUBE_LINK_MESSAGE_LINKAGE void ShowGameCubeLinkMessage(u32 stringId)
{
    FillBgTilemapRect(2, 2, 0x10, 0x1A, 4, 0);
    SelectTextFont(2, 0, 0);
    PrintTextBox(0xA1, 0x78, 0x80, 0xC8, GetDialogText(stringId), 1);
}
