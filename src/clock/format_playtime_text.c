#include "clock.h"
#include "hw/bios.h"
#include "math.h"
#include "save.h"
#include "text.h"

// Expands text textId into out, replacing @D (wHourCarry), @H/@h hours, @M/@m
// minutes, @S/@s seconds and @A/@a AM/PM letters. Any @A/@a switches hours to a
// 12-hour clock. Returns out.
u8 *FormatPlaytimeText(const Playtime *playtime, u8 *out, s32 textId)
{
    u8 *format;
    u8 *scan;
    u8 *start;
    s32 twelveHour;
    s32 hours;
    s32 remainder;

    format = GetDialogText(textId);
    scan = format;
    twelveHour = 0;
    while (*scan != '\0')
    {
        if (*scan == '@')
        {
            scan++;
            if (*scan == 'a' || *scan == 'A')
            {
                twelveHour = 1;
                break;
            }
        }
        scan++;
    }

    start = out;
    while (*format != '\0')
    {
        if (*format == '@')
        {
            format++;
            switch (*format)
            {
            case 'D':
                if (playtime->wHourCarry > 99)
                    *out++ = bios_Mod(bios_Div(playtime->wHourCarry, 100), 10) + '0';
                if (playtime->wHourCarry > 9)
                    *out++ = bios_Mod(bios_Div(playtime->wHourCarry, 10), 10) + '0';
                *out++ = bios_Mod(playtime->wHourCarry, 10) + '0';
                if (format[1] == 'D')
                    format++;
                break;
            case 'a':
                *out++ = playtime->bHours <= 11 ? 'a' : 'p';
                break;
            case 'A':
                *out++ = playtime->bHours <= 11 ? 'A' : 'P';
                break;
            case 'H':
            case 'h':
                if (twelveHour)
                {
                    hours = playtime->bHours;
                    if (hours > 12)
                        hours -= 12;
                    if (hours <= 0)
                        hours += 12;
                    *out++ = hours <= 9 ? ' ' : '1';
                }
                else
                {
                    *out++ = bios_Div(playtime->bHours, 10) + '0';
                    hours = playtime->bHours;
                }
                *out++ = bios_Mod(hours, 10) + '0';
                format++;
                break;
            case 'M':
            case 'm':
                *out++ = iwramDivideSignedRemainder(playtime->bMinutes, 10, &remainder) + '0';
                *out++ = remainder + '0';
                format++;
                break;
            case 'S':
            case 's':
                *out++ = bios_Div(playtime->bSeconds, 10) + '0';
                *out++ = bios_Mod(playtime->bSeconds, 10) + '0';
                format++;
                break;
            }
        }
        else
        {
            *out++ = *format;
        }
        format++;
    }
    *out = '\0';
    return start;
}
