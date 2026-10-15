#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "mem.h"
#include "actor.h"
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

    for (i = 0; i < ARRAY_COUNT(g_OptionsState.apActors); i++)
    {
        FreeActor(g_OptionsState.apActors[i]);
        g_OptionsState.apActors[i] = NULL;
    }

    FreeAllActors(&g_ActiveActorListState.pHead);
    DisableKrawall();
    SyncSaveHeaderIfDirty();
    EnableKrawall();
}
