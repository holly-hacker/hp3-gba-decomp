#include "interrupts.h"

// A NULL callback installs IntrDummy rather than clearing the slot.
void SetVCountCallback(void (*callback)(void))
{
    if (callback == NULL)
        g_pVBlankState->pVCountCallback = IntrDummy;
    else
        g_pVBlankState->pVCountCallback = callback;
}
