#include "mt19937.h"
#include "mem.h"

void Mt19937AllocState(void)
{
    gMt19937StatePtr = AllocBlock(MT_STATE_WORDS * sizeof(u32));
}
