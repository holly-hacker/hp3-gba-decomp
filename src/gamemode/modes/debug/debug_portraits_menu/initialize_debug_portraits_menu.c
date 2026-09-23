#include "types.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "room.h"

void InitializeDebugPortraitsMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(1);
    SetDispcntFlag(0x1000);
    SetBgControl(1, g_dwDebugPortraitsBg1Control);
    LoadBgGraphic(1, g_DebugMenuGraphic, 0, 0, 0, 0);

    g_DebugPortraitsState.dwSelection = 0;
    g_DebugPortraitsState.pPortraitObject = 0;
    sub_0800B52C();
    g_GameModeStackContext.dwModeState = 0;

    PlayScreenTransitionInByIndex(0x3F, 2);
}
