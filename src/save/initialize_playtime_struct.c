#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Zeroes a playtime counter.
void InitializePlaytimeStruct(Playtime *playtime)
{
    memset(playtime, 0, sizeof(Playtime));
}
