#include "interrupts.h"

void ResetIntrFunc(u32 slot)
{
    gIntrTable[slot] = gIntrTableTemplate[slot];
}
