#include "types.h"
#include "audio.h"
#include "display.h"
#include "main_menu.h"
#include "mem.h"
#include "options.h"
#include "save.h"

void ExitOptions(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (!g_saveManager.header.bHeaderFlags.bits.bGammaHigh)
        ApplyGammaRemapTable(g_abGammaNormalRemap);
    else
        ApplyGammaRemapTable(g_abGammaHighRemap);

    sub_0801E0DC();

    for (i = 0; i < 8; i++)
    {
        FreeObject(g_OptionsState.apObjects[i]);
        g_OptionsState.apObjects[i] = NULL;
    }

    FreeAllObjects(&g_ActiveObjectListState.pHead);
    DisableKrawall();
    SyncSaveHeaderIfDirty();
    EnableKrawall();
}
