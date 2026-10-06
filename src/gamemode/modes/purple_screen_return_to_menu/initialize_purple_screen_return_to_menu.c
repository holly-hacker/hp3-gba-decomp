#include "types.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "menu/purple_screen.h"

void InitializePurpleScreenReturnToMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;

    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwPurpleScreenBg0Control);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
