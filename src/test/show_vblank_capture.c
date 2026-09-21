#include "types.h"
#include "display.h"
#include "main_menu.h"
#include "text.h"

static const u32 sPowersOfTen[10] = {
    1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1,
};

// TEST ROM: prints g_dwTestVBlankCapture in hex and decimal on the main menu.
void ShowTestVBlankCapture(void)
{
    u32 count;
    u32 cursor;
    u32 value;
    u32 i;
    u32 digit;
    u32 started;
    u8 *pOut;
    u8 line[24];
    u8 *pText;

    count = g_dwTestVBlankCapture;
    ClearBgTilemap_candidate(1);
    SelectTextFont_candidate(2, 6, -1);

    pOut = line;
    *pOut++ = 'V';
    *pOut++ = 'B';
    *pOut++ = 'L';
    *pOut++ = 'A';
    *pOut++ = 'N';
    *pOut++ = 'K';
    *pOut++ = ' ';
    *pOut++ = '0';
    *pOut++ = 'x';
    for (i = 0; i < 8; i++)
    {
        digit = (count >> (28 - i * 4)) & 0xF;
        *pOut++ = digit < 10 ? '0' + digit : 'A' + digit - 10;
    }
    *pOut = 0;
    pText = line;
    cursor = DrawTextLines_candidate(g_dwMainMenuTextCursor, 0x78, 0x70, 0xE0, 0x10, &pText, 1);

    pOut = line;
    started = 0;
    value = count;
    for (i = 0; i < 10; i++)
    {
        digit = 0;
        while (value >= sPowersOfTen[i])
        {
            value -= sPowersOfTen[i];
            digit++;
        }
        if (digit != 0 || started || i == 9)
        {
            *pOut++ = '0' + digit;
            started = 1;
        }
    }
    *pOut = 0;
    pText = line;
    DrawTextLines_candidate(cursor, 0x78, 0x84, 0xE0, 0x10, &pText, 1);
}
