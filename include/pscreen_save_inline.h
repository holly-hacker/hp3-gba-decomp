#pragma once

#include "font.h"
#include "text.h"
#include "pscreen_save.h"

// The ROM compiles this into ResolveSaveConfirmation and also keeps an out-of-line copy, as one
// translation unit with an inline definition would. The file that emits the out-of-line copy
// defines the linkage macro as empty.
#ifndef SHOW_SAVING_MESSAGE_LINKAGE
#define SHOW_SAVING_MESSAGE_LINKAGE extern inline
#endif

SHOW_SAVING_MESSAGE_LINKAGE void ShowSavingMessage(void)
{
    SelectTextFont(1, 0, -1);
    PrintTextBox(0xC1, 0x78, 0x48, 0x90, GetDialogText(0x592), 1);  // "Saving Game..."
}
