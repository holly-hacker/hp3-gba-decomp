#include "interrupts.h"
#include "interrupts_inline.h"

void RestoreDefaultVBlankCallback(void)
{
    SetVBlankCallbackInline(VBlankCallback);
}
