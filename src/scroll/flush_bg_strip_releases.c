#include "types.h"
#include "scroll.h"

// Releases the tiles of the queued column and row, then records the current scroll as loaded.
void FlushBgStripReleases(void)
{
    u32 i;

    for (i = 0; i < 2; i++)
    {
        if (g_aBgStripReleases[i].x != BG_STRIP_NONE)
        {
            if (i == 0)
                ReleaseBgTileColumn(g_aBgStripReleases[i].x, g_aBgStripReleases[i].y);
            else
                ReleaseBgTileRow(g_aBgStripReleases[i].x, g_aBgStripReleases[i].y);
            g_aBgStripReleases[i].x = BG_STRIP_NONE;
            g_aBgStripReleases[i].y = BG_STRIP_NONE;
        }
    }

    g_BgLoadedScroll = g_BgScroll;
}
