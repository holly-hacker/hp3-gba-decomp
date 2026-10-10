#include "math.h"
#include "hw/bios.h"

// Rounds the angle of a 16.16 vector to one of 32 steps, rotated a quarter
// turn from the BIOS ArcTan2 origin.
u8 GetDirection32FromVector(FixedPoint v)
{
    u32 angle;

    v.x >>= 16;
    v.y >>= 16;
    angle = (u16)bios_ArcTan2(v.x, v.y);
    return (((angle * 32 + 0x800) >> 16) + 8) & 0x1F;
}
