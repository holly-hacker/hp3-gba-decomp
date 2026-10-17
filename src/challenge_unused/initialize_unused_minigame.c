#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "challenge_unused.h"

void InitializeUnusedMinigame(void)
{
    u16 fillValue;
    u16 *pFillValue;

    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwUnusedMinigameBg0Control);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
