#include "sound.h"
#include "hw/io_regs.h"

// Masks the Timer 1 interrupt that drives kradInterrupt.
void DisableKrawallTimerInterrupt(void)
{
    REG_IME = 0;
    REG_IE &= ~0x10;
    REG_IME = 1;
}
