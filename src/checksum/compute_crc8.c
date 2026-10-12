#include "checksum.h"

u8 ComputeCrc8(const u8 *data, u32 len)
{
    u32 crc;
    u32 byte;
    u32 mix;
    u32 bit;

    crc = 0;
    while (len-- != 0)
    {
        byte = *data;
        for (bit = 0; bit < 8; bit++)
        {
            mix = (crc ^ byte) & 1;
            byte >>= 1;
            crc >>= 1;
            if (mix != 0)
                crc ^= 0x8C;
        }
        data++;
    }
    return crc;
}
