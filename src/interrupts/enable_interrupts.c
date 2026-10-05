#include "hw/vblank.h"
#include "hw/interrupts.h"
#include "hw/io_regs.h"

// Enables the VBlank and Timer 1 (IwramTimer1Handler) interrupts and the
// VBlank IRQ in DISPSTAT, then turns on IME.
void EnableInterrupts(void)
{
    REG_IE = 0x11;
    REG_DISPSTAT = 8;
    g_wPendingIntrFlags &= 0xFFFE;
    REG_IME = 1;
}
