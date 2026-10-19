#pragma once

#include "lcd.h"
#include "hw/io_regs.h"

// LCD logic that the ROM compiles inline into the other LCD helpers.

// The body of WaitForVBlankFlag: polls DISPSTAT's VBlank flag.
static inline void WaitForVBlankFlagInline(void)
{
    while (1) {
        if (REG_DISPSTAT & DISPSTAT_VBLANK)
            break;
    }
}
