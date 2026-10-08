#include "trig.h"

s16 Sin8_8(u8 angle)
{
    return g_anSineTable[angle] >> 8;
}
