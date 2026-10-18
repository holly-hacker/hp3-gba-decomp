#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_save.h"

void ShowGameSavedMessage(void)
{
    ClearBgTilemapRect(2, 3, 6, 0x18, 8);
    SelectTextFont(1, 0, -1);
    PrintTextBox(0xC1, 0x78, 0x48, 0x90, GetDialogText(0x593), 1);  // "Game Saved"
    PrintTextBox(0xF1, 0x78, 0x58, 0x90, GetDialogText(0x591), 1);  // "Press any button to continue"
}
