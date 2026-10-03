#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "menu/options.h"
#include "game/save.h"

void ExitOptions(void)
{
    u32 i;

    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (!g_saveManager.header.bHeaderFlags.bits.bGammaHigh)
        ApplyGammaRemapTable(g_abGammaNormalRemap);
    else
        ApplyGammaRemapTable(g_abGammaHighRemap);

    ExitMenuScreen();

    for (i = 0; i < ARRAY_COUNT(g_OptionsState.apObjects); i++)
    {
        FreeObject(g_OptionsState.apObjects[i]);
        g_OptionsState.apObjects[i] = NULL;
    }

    FreeAllObjects(&g_ActiveObjectListState.pHead);
    DisableKrawall();
    SyncSaveHeaderIfDirty();
    EnableKrawall();
}
