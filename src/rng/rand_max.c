#include "mt19937.h"

u32 Mt19937RandMax(u16 max)
{
    u32 result = Mt19937Next();
    result &= 0x7FFFu;
    result *= max + 1;
    return (result << 1) >> 16;
}
