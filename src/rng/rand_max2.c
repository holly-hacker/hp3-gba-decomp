#include "mt19937.h"

u32 Mt19937RandMax2(u16 max)
{
    u32 result = Mt19937Next2();
    result &= 0x7FFFu;
    result *= max + 1;
    return (result << 1) >> 16;
}
