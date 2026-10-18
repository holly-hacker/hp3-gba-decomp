#include "font.h"
#include "text.h"
#include "pause_menu.h"
#include "pscreen_save.h"

void ShowSaveConfirmationPrompt(u32 stringId)
{
    BuildListMenu(&g_SaveConfirmationMenuDefinition);
    SelectTextFont(1, 0, -1);
    PrintTextBox(0xC1, 0x78, 0x38, 0x90, GetDialogText(stringId), 1);
}
