#include "pscreen_information_inline.h"

void SetHelpMenuSelection(u32 entry)
{
    if (g_HelpState.bSelectedEntry != entry)
    {
        DrawHelpMenuEntry(g_HelpState.bSelectedEntry, 0);
        g_HelpState.bSelectedEntry = entry;
        DrawHelpMenuEntry(g_HelpState.bSelectedEntry, 6);
    }
}
