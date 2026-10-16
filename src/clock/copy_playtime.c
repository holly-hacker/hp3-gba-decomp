#include "types.h"
#include "clock.h"
#include "game/save.h"

void CopyPlaytime(Playtime *dst, const Playtime *src)
{
    *dst = *src;
}
