#pragma once

#include "interrupts.h"

// Interrupt logic that the ROM compiles inline into other interrupt routines.

// The body of SetVBlankCallback. A NULL callback installs IntrDummy rather
// than clearing the slot.
static inline void SetVBlankCallbackInline(void (*callback)(void))
{
    if (callback == NULL)
        g_pVBlankState->pVBlankCallback = IntrDummy;
    else
        g_pVBlankState->pVBlankCallback = callback;
}
