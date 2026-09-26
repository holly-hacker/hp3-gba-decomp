#include "types.h"
#include "divide.h"
#include "text.h"

// Writes value as signed decimal text to pBuf and returns pBuf. Leading
// zeros are dropped, and gLocaleThousandsSep follows the billions, millions
// and thousands digits.
u8 *FormatDecimal(s32 value, u8 *pBuf)
{
    u8 *pOut;
    s32 remainder;
    s32 digit;

    pOut = pBuf;
    remainder = value;
    digit = -1;
    if (value < 0)
    {
        remainder = -value;
        *pOut++ = '-';
    }
    if (remainder >= 1000000000)
    {
        digit = iwramDivideSignedRemainder(remainder, 1000000000, &remainder);
        *pOut++ = digit + '0';
        *pOut++ = gLocaleThousandsSep;
    }
    if (remainder >= 100000000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 100000000, &remainder);
        *pOut++ = digit + '0';
    }
    if (remainder >= 10000000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 10000000, &remainder);
        *pOut++ = digit + '0';
    }
    if (remainder >= 1000000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 1000000, &remainder);
        *pOut++ = digit + '0';
        *pOut++ = gLocaleThousandsSep;
    }
    if (remainder >= 100000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 100000, &remainder);
        *pOut++ = digit + '0';
    }
    if (remainder >= 10000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 10000, &remainder);
        *pOut++ = digit + '0';
    }
    if (remainder >= 1000 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 1000, &remainder);
        *pOut++ = digit + '0';
        *pOut++ = gLocaleThousandsSep;
    }
    if (remainder >= 100 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 100, &remainder);
        *pOut++ = digit + '0';
    }
    if (remainder >= 10 || digit != -1)
    {
        digit = iwramDivideSignedRemainder(remainder, 10, &remainder);
        *pOut++ = digit + '0';
    }
    pOut[0] = remainder + '0';
    pOut[1] = 0;
    return pBuf;
}
