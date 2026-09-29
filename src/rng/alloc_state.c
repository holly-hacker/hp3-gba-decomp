#include "mt19937.h"
#include "hw/mem.h"

void Mt19937AllocState(void)
{
    gMt19937StatePtr = AllocBlock(MT_STATE_WORDS * sizeof(u32));
}
