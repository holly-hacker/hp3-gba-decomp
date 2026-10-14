#include "types.h"
#include "background.h"
#include "cheat_map.h"

void ScrollCheatMap(u32 scrollUp)
{
    s32 scrollY;

    scrollY = g_CheatMapState.nScrollY;
    if (scrollUp)
        g_CheatMapState.nScrollY = scrollY - 8;
    else
        g_CheatMapState.nScrollY = scrollY + 8;

    g_CheatMapState.nScrollY %= 0x200;
    SetBgScrollFixed(1, 0, g_CheatMapState.nScrollY << 16);
}
