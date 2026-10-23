#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "main.h"
#include "modes.h"
#include "scroll.h"

// Moves the camera toward GetCameraTargetPosition (at most 8 pixels per axis unless `snap`),
// streams in the tile column and row that scroll into view and queues the ones that left
// it for release, then scrolls the enabled BG layers.
void UpdateOverworldCamera(u32 snap)
{
    u32 reset = 0;
    IntPoint pos;
    s32 layer;

    pos = GetCameraTargetPosition();
    if (snap == 0)
    {
        pos.x = StepScrollToward(g_BgScroll.x, pos.x);
        pos.y = StepScrollToward(g_BgScroll.y, pos.y);
    }
    g_CameraPosition.nX = pos.x;
    g_CameraPosition.nY = pos.y;

    if (!(g_dwGameModeFlags & (GameModeFlagFreezeView | GameModeFlagFreezeViewOnExit)))
    {
        if (snap == 0)
        {
            FlushBgStripReleases();
            if (g_BgScroll.x >> 3 != pos.x >> 3)
            {
                if (g_BgScroll.x > pos.x)
                {
                    LoadBgTileColumn(pos.x, g_BgScroll.y);
                    QueueBgStripRelease(pos.x + 248, g_BgScroll.y, 0);
                }
                else
                {
                    LoadBgTileColumn(pos.x + SCREEN_WIDTH, g_BgScroll.y);
                    QueueBgStripRelease(pos.x - 8, g_BgScroll.y, 0);
                }
            }
            if (g_BgScroll.y >> 3 != pos.y >> 3)
            {
                if (g_BgScroll.y > pos.y)
                {
                    LoadBgTileRow(pos.x, pos.y);
                    QueueBgStripRelease(pos.x, pos.y + 168, 1);
                }
                else
                {
                    LoadBgTileRow(pos.x, pos.y + SCREEN_HEIGHT);
                    QueueBgStripRelease(pos.x, pos.y - 8, 1);
                }
            }
        }
        g_BgScroll.x = pos.x;
        g_BgScroll.y = pos.y;
    }
    else
    {
        g_BgScroll.x = reset;
        g_BgScroll.y = reset;
    }

    for (layer = 0; layer < 4; layer++)
    {
        if (g_adwBgScrollEnabled[layer])
            SetBgScroll(layer, pos.x, pos.y);
    }
}
