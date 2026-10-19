#include "clock.h"
#include "save.h"

// Returns 1 if playtime lies within start..end (inclusive), comparing the
// ComparePlaytimeField fields in fieldMask. End before start wraps around, and
// start equal to end matches everything.
u32 IsPlaytimeInRange(const Playtime *start, const Playtime *end, const Playtime *playtime,
                      u32 fieldMask)
{
    u32 startVsEnd;
    u32 vsStart;
    u32 vsEnd;

    startVsEnd = ComparePlaytimeField(start, end, fieldMask);
    vsStart = ComparePlaytimeField(playtime, start, fieldMask);
    vsEnd = ComparePlaytimeField(playtime, end, fieldMask);
    if (startVsEnd == 1 && (vsStart == 1 || vsEnd == 2))
        return 0;
    if (startVsEnd == 2 && vsStart == 1 && vsEnd == 2)
        return 0;
    return 1;
}
