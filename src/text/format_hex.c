#include "types.h"
#include "text.h"

// Writes the low digitCount hex digits of value, uppercase and zero-padded,
// to pBuf and returns pBuf.
u8 *FormatHex(s32 value, s32 digitCount, u8 *pBuf)
{
    u8 *pStart;
    s32 i;
    s32 digit;

    pStart = pBuf;
    for (i = digitCount - 1; i >= 0; i--)
    {
        digit = (value >> (i * 4)) & 0xF;
        if (digit <= 9)
            *pBuf++ = digit + '0';
        else
            *pBuf++ = digit + 'A' - 10;
        value -= digit << (i * 4);
    }
    *pBuf = 0;
    return pStart;
}
