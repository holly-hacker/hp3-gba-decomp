#include "types.h"
#include "mem.h"
#include "game/save.h"

// Zeroes a playtime counter.
void InitializePlaytimeStruct(Playtime *playtime)
{
    memset(playtime, 0, sizeof(Playtime));
}
