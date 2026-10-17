#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "cheat_portraits.h"
#include "graphics/display.h"
#include "modes.h"
#include "hw/io_regs.h"
#include "overworld/room.h"
#include "screen_transitions.h"

void InitializeCheatPortraits(void)
{
    u16 fillValue;
    u16 *pFillValue;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(1);
    SetDispcntFlag(0x1000);
    SetBgControl(1, g_dwCheatPortraitsBg1Control);
    LoadBgGraphic(1, gDebugMenuGraphic, 0, 0, 0, 0);

    g_CheatPortraitsState.dwSelection = 0;
    g_CheatPortraitsState.pPortraitActor = 0;
    ShowCheatPortrait();
    g_GameModeStackContext.dwModeState = 0;

    PlayScreenTransitionInByIndex(0x3F, 2);
}
