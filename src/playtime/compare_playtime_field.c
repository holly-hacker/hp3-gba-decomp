#include "playtime.h"

u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask)
{
    s32 left;
    s32 right;

    if (fieldMask & 8)
    {
        left = playtime->wHourCarry;
        right = mask->wHourCarry;
        if (left != right)
            goto unequal;
    }

    if (fieldMask & 4)
    {
        left = playtime->bHours;
        right = mask->bHours;
        if (left != right)
            goto unequal;
    }

    if (fieldMask & 2)
    {
        left = playtime->bMinutes;
        right = mask->bMinutes;
        if (left != right)
        {
            goto unequal;
        unequal:
            return left < right ? 1 : 2;
        }
    }

    if (fieldMask & 1)
    {
        s32 secLeft;
        s32 secRight;

        secLeft = playtime->bSeconds;
        secRight = (s8)((const u8 *)mask)[4];
        if (secLeft == secRight)
            return 0;
        return secLeft < secRight ? 1 : 2;
    }

    return 0;
}
