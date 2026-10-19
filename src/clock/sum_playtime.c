#include "clock.h"
#include "save.h"

// Stores playtime + toAdd in sum, leaving playtime unchanged.
void SumPlaytime(const Playtime *playtime, const Playtime *toAdd, Playtime *sum)
{
    *sum = *playtime;
    AddPlaytimeDelta(sum, toAdd);
}
