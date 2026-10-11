#include "types.h"
#include "graphics/display.h"
#include "actor.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "menu/dialog.h"
#include "menu/loading_screen.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitLoadingScreen(void)
{
    s32 i;

    ClearScanlineEffects();
    StopScanlineEffects();
    bios_CPUFastSet(g_awSavedBgPalette0, BG_PLTT, 8);
    SetBgPriority(2, g_LoadingScreenState.bSavedBg2Priority);
    g_abQuestEventState[0x12] = g_abQuestEventState[0];
    SetActorActionState(g_pPlayerObject, 0x21);
    sub_0801FA9C();
    HideScreenWindow_candidate(0);

    FreeActor(g_LoadingScreenState.pCursorObject);
    for (i = 0; i < LOADING_SCREEN_OPTION_COUNT; i++)
        FreeActor(g_LoadingScreenState.apOptionObjects[i]);

    ReserveObjPaletteSlot(1);
    ReserveObjPaletteSlot(2);
    if (g_bCurrentRoomId == 1)
        SetAlphaBlendTargets(4, 0x1F);
}
