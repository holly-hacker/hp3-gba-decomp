#include "types.h"
#include "background.h"
#include "pouring_minigame.h"

// Only the bartender's lane can pour; BG1 is redrawn where a tap changed.
void DrawServePumpkinJuiceTaps(void)
{
    s32 lane;

    for (lane = 0; lane < SERVE_PUMPKIN_JUICE_LANE_COUNT; lane++)
    {
        if (g_ServePumpkinJuice.dwLane != lane)
            g_ServePumpkinJuice.aabTapPouring[lane][0] = 0;

        if (g_ServePumpkinJuice.aabTapPouring[lane][0] != g_ServePumpkinJuice.aabTapPouring[lane][1])
        {
            if (g_ServePumpkinJuice.aabTapPouring[lane][0])
                CopyBgTilemapRect(1, g_ServePumpkinJuice.pBg1Tilemap, 1, 0, 0, 20, g_aServePumpkinJuiceTapCells[lane].x,
                                  g_aServePumpkinJuiceTapCells[lane].y, 2, 3);
            else
                CopyBgTilemapRect(1, g_ServePumpkinJuice.pBg1Tilemap, 1, 0, 2, 20, g_aServePumpkinJuiceTapCells[lane].x,
                                  g_aServePumpkinJuiceTapCells[lane].y, 2, 3);

            g_ServePumpkinJuice.aabTapPouring[lane][1] = g_ServePumpkinJuice.aabTapPouring[lane][0];
        }
    }
}
