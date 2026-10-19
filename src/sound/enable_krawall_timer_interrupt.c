#include "sound.h"
#include "hw/io_regs.h"

// Unmasks the Timer 1 interrupt that drives kradInterrupt.
void EnableKrawallTimerInterrupt(void)
{
    REG_IME = 0;
    REG_IE |= 0x10;
    REG_IME = 1;
}
