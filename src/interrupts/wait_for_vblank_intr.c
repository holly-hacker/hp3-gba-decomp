#include "types.h"
#include "vblank.h"
#include "bios.h"

// Clears the pending-vblank flag, then sleeps until the next vblank interrupt.
void WaitForVBlankIntr(void)
{
    g_wPendingIntrFlags &= 0xFFFE;
    bios_VBlankIntrWait();
}
