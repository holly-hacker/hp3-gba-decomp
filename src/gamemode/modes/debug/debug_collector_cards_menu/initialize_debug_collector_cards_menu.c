#include "types.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "room.h"
#include "text.h"
#include "wizard_cracker_pop_it.h"

void InitializeDebugCollectorCardsMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl2;
    const u8 *pGraphic;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugCollectorCardsBg0Control);
    SetBgControl(1, g_dwDebugCollectorCardsBg1Control);
    bgCtrl2 = g_dwDebugCollectorCardsBg2Control;
    SetBgControl(2, bgCtrl2);
    SetTextTargetFromBgControl(bgCtrl2);
    LoadBgGraphic(0, g_DebugCollectorCardsBg0Graphic, 0, 0, 0, 0);
    pGraphic = g_DebugMenuGraphic;
    sub_080077C8(1, pGraphic, 0, 0, 0, 0);
    LoadEmbeddedPalette_candidate((u8 *)pGraphic, 0, 3);
    sub_08007AF0(0, 0xFFCA0000, 0xFFE20000);

    g_DebugCollectorCardsState.dwSelection = 0;
    g_DebugCollectorCardsState.pCardObject = 0;
    g_GameModeStackContext.dwModeState = 0;
    sub_0800BAF8();

    PlayScreenTransitionInByIndex(0x3F, 2);
}
