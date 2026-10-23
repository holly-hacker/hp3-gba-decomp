#include "background.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "dialog.h"
#include "dialog_box.h"

void RestoreBgAboveDialogBox(void)
{
    if (g_DialogState.dwState != 0)
    {
        bios_CPUFastSet(g_awSavedBgPalette0, BG_PLTT, 8);
        SetBgPriority(0, g_adwSavedBgPriority[0]);
        SetBgPriority(1, g_adwSavedBgPriority[1]);
        if (g_DialogState.dwState == 2)
            g_DialogState.dwState = 0;
    }
}
