#include "checksum.h"

u8 ComputeJoybusChecksum(u16 value)
{
    u32 crc;
    u32 data;
    u32 mask;
    u32 i;

    data = value;
    crc = 0;
    i = 2;
    while (i != 0)
    {
        for (mask = 0x80; mask != 0; mask >>= 1)
        {
            crc <<= 1;
            if (data & mask)
            {
                if (crc & 0x100)
                    crc ^= 0xCC;
                else
                    crc++;
            }
            else if (crc & 0x100)
            {
                crc ^= 0xCD;
            }
        }
        data >>= 8;
        i--;
    }

    while (i < 8)
    {
        crc <<= 1;
        if (crc & 0x100)
            crc ^= 0xCD;
        i++;
    }
    return crc;
}
