#include "trig.h"

s16 Cos8_8(u8 angle)
{
    return g_anSineTable[(angle + 0x40) & 0xFF] >> 8;
}
