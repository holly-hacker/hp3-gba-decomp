#include "types.h"
#include "hw/vblank.h"
#include "hw/bios.h"

// Clears the pending-vblank flag, then sleeps until the next vblank interrupt.
void WaitForVBlankIntr(void)
{
    g_wPendingIntrFlags &= 0xFFFE;
    bios_VBlankIntrWait();
}
