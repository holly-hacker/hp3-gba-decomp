#include "hw/vblank.h"
#include "hw/interrupts.h"

// A NULL callback installs IntrDummy rather than clearing the slot.
void SetVBlankCallback(void *callback)
{
    if (callback == NULL)
        g_pVBlankState->pVBlankCallback = IntrDummy;
    else
        g_pVBlankState->pVBlankCallback = callback;
}
