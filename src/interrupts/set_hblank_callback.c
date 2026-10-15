#include "interrupts.h"

// A NULL callback installs IntrDummy rather than clearing the slot.
void SetHBlankCallback(void (*callback)(void))
{
    if (callback == NULL)
        g_pVBlankState->pHBlankCallback = IntrDummy;
    else
        g_pVBlankState->pHBlankCallback = callback;
}
