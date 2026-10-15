#include "interrupts.h"

void SetIntrFunc(u32 slot, IntrFunc pfnHandler)
{
    gIntrTable[slot] = pfnHandler;
}
