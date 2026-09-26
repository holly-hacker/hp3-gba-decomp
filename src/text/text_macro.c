#include "types.h"
#include "dialog.h"
#include "text.h"

// Fill text macro @N (sTextMacroTable slot N - 1) before showing text that uses it.
// JP copies a two-byte glyph (lead byte above 0xEF) as a unit.

void SetTextMacroString(const u8 *pString, u32 slot)
{
    u8 *pDest;

    pDest = sTextMacroTable[slot];
    while (*pString != 0)
    {
#ifdef VERSION_JP
        if (*pString > 0xEF)
            *pDest++ = *pString++;
#endif
        *pDest++ = *pString++;
    }
    *pDest = 0;
}

void SetTextMacro1String(const u8 *pString)
{
    u8 *pDest;

    pDest = sTextMacroTable[0];
    while (*pString != 0)
    {
#ifdef VERSION_JP
        if (*pString > 0xEF)
            *pDest++ = *pString++;
#endif
        *pDest++ = *pString++;
    }
    *pDest = 0;
}

void SetTextMacro2String(const u8 *pString)
{
    u8 *pDest;

    pDest = sTextMacroTable[1];
    while (*pString != 0)
    {
#ifdef VERSION_JP
        if (*pString > 0xEF)
            *pDest++ = *pString++;
#endif
        *pDest++ = *pString++;
    }
    *pDest = 0;
}

void SetTextMacro3String(const u8 *pString)
{
    u8 *pDest;

    pDest = sTextMacroTable[2];
    while (*pString != 0)
    {
#ifdef VERSION_JP
        if (*pString > 0xEF)
            *pDest++ = *pString++;
#endif
        *pDest++ = *pString++;
    }
    *pDest = 0;
}

void SetTextMacroNumber(s32 value, u32 slot)
{
    FormatDecimal(value, sTextMacroTable[slot]);
}

void SetTextMacro1Number(s32 value)
{
    FormatDecimal(value, sTextMacroTable[0]);
}

void SetTextMacro2Number(s32 value)
{
    FormatDecimal(value, sTextMacroTable[1]);
}

void SetTextMacro3Number(s32 value)
{
    FormatDecimal(value, sTextMacroTable[2]);
}
