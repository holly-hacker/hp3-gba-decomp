#include "hw/vblank.h"
#include "hw/interrupts.h"

// A NULL callback installs IntrDummy rather than clearing the slot.
void SetVCountCallback(void *callback)
{
    if (callback == NULL)
        g_pVBlankState->pVCountCallback = IntrDummy;
    else
        g_pVBlankState->pVCountCallback = callback;
}
