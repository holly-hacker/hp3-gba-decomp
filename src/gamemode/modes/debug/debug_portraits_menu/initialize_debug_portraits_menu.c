#include "types.h"
#include "hw/bios.h"
#include "menu/debug_menu.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "overworld/room.h"

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
    LoadBgGraphic(1, gDebugMenuGraphic, 0, 0, 0, 0);

    g_DebugPortraitsState.dwSelection = 0;
    g_DebugPortraitsState.pPortraitObject = 0;
    sub_0800B52C();
    g_GameModeStackContext.dwModeState = 0;

    PlayScreenTransitionInByIndex(0x3F, 2);
}
