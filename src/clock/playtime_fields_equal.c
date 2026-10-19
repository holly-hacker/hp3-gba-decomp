#include "clock.h"
#include "save.h"

// Returns 1 if every field selected by fieldMask is equal: 0x08 wHourCarry,
// 0x04 hours, 0x02 minutes, 0x01 seconds, 0x10 frames.
u32 PlaytimeFieldsEqual(const Playtime *left, const Playtime *right, u32 fieldMask)
{
    u32 equal;

    equal = 1;
    if ((fieldMask & 8) && left->wHourCarry != right->wHourCarry)
        equal = 0;
    if ((fieldMask & 4) && left->bHours != right->bHours)
        equal = 0;
    if ((fieldMask & 2) && left->bMinutes != right->bMinutes)
        equal = 0;
    if ((fieldMask & 1) && left->bSeconds != right->bSeconds)
        equal = 0;
    if ((fieldMask & 0x10) && left->bFrames != right->bFrames)
        equal = 0;
    return equal;
}
