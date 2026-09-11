#include "playtime.h"

// Adds a small delta to a running playtime counter, normalising each field
// in turn (frames mod 30, seconds and minutes mod 60, hours mod 99) and
// OR-ing a bit into the return value for every field that carried.
u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd)
{
    s32 value;
    u32 carry;
    // Frames' overflow-loop locals live at function scope, unlike the other
    // three fields' -- needed to reproduce the ROM's register choice here.
    u32 bit;
    s32 carried;
    s32 nextValue;
    u32 nextCount;
    u32 count;

    carry = 0;
    value = (u8)toAdd->bFrames + (count = (u8)playtime->bFrames);
    playtime->bFrames = value;

    if ((s8)value < 0)
    {
        do
        {
            playtime->bFrames = (u8)playtime->bFrames + 30;
            playtime->bSeconds = (u8)playtime->bSeconds - 1;
            carry |= 1;
        } while (playtime->bFrames < 0);

    }
    else
    {
        if ((s8)value > 29)
        {
            bit = 1;
            carried = value;
            count = (u8)playtime->bSeconds;
            do
            {
                nextValue = carried;
                nextValue -= 30;
                carried = nextValue;
                nextCount = count;
                nextCount += 1;
                count = nextCount;
                carry |= bit;
            } while ((s8)nextValue > 29);
            playtime->bSeconds = nextCount;
            playtime->bFrames = nextValue;
        }
    }

    value = (u8)playtime->bSeconds;
    value += (u8)toAdd->bSeconds;
    playtime->bSeconds = value;
    if ((s8)value < 0)
    {
        do
        {
            playtime->bSeconds = (u8)playtime->bSeconds + 60;
            playtime->bMinutes = (u8)playtime->bMinutes - 1;
            carry |= 2;
        } while (playtime->bSeconds < 0);
    }
    else if ((s8)value > 59)
    {
        u32 bit;
        s32 carried;
        s32 nextValue;
        u32 nextCount;
        u32 count;

        bit = 2;
        carried = value;
        count = (u8)playtime->bMinutes;
        do
        {
            nextValue = carried;
            nextValue -= 60;
            carried = nextValue;
            nextCount = count;
            nextCount += 1;
            count = nextCount;
            carry |= bit;
        } while ((s8)nextValue > 59);
        playtime->bMinutes = nextCount;
        playtime->bSeconds = nextValue;
    }

    value = (u8)playtime->bMinutes;
    value += (u8)toAdd->bMinutes;
    playtime->bMinutes = value;
    if ((s8)value < 0)
    {
        do
        {
            playtime->bMinutes = (u8)playtime->bMinutes + 60;
            playtime->bHours = (u8)playtime->bHours - 1;
            carry |= 4;
        } while (playtime->bMinutes < 0);
    }
    else if ((s8)value > 59)
    {
        u32 bit;
        s32 carried;
        s32 nextValue;
        u32 nextCount;
        u32 count;

        bit = 4;
        carried = value;
        count = (u8)playtime->bHours;
        do
        {
            nextValue = carried;
            nextValue -= 60;
            carried = nextValue;
            nextCount = count;
            nextCount += 1;
            count = nextCount;
            carry |= bit;
        } while ((s8)nextValue > 59);
        playtime->bHours = nextCount;
        playtime->bMinutes = nextValue;
    }

    value = (u8)playtime->bHours;
    value += (u8)toAdd->bHours;
    playtime->bHours = value;
    if ((s8)value < 0)
    {
        do
        {
            playtime->bHours = (u8)playtime->bHours + 99;
            playtime->wHourCarry--;
            carry |= 8;
        } while (playtime->bHours < 0);
    }
    else if ((s8)value > 98)
    {
        u32 bit;
        s32 carried;
        s32 nextValue;
        u32 nextCount;
        u32 count;

        bit = 8;
        carried = value;
        count = (u16)playtime->wHourCarry;
        do
        {
            nextValue = carried;
            nextValue -= 99;
            carried = nextValue;
            nextCount = count;
            nextCount += 1;
            // do/while(0) is a register-allocation proxy, not real control
            // flow -- it nudges loop-depth-weighted priority to get the
            // ROM's r3/r1 split. Replace by reproducing the bytes, not by
            // preserving this construct.
            do { count = nextCount; carry |= bit; } while (0);
        } while ((s8)nextValue > 98);
        playtime->wHourCarry = nextCount;
        playtime->bHours = nextValue;
    }

    return carry;
}
