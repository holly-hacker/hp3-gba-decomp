#include "interrupts.h"
#include "interrupts_inline.h"

void SetVBlankCallback(void (*callback)(void))
{
    SetVBlankCallbackInline(callback);
}
