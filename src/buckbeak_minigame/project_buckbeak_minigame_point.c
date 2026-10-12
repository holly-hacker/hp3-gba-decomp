#include "types.h"
#include "math.h"
#include "buckbeak_minigame.h"

// Projects a world position onto the screen from the camera's point of view.
// Returns 0, with the depth left far away, when the point is out of view.
u8 ProjectBuckbeakMinigamePoint(BuckbeakMinigameProjection *pPoint)
{
    FixedPoint offset;
    u32 distance;
    s32 limit;
    s32 scale;
    s32 x;
    s32 y;

    distance = ApproximateDistance(pPoint->world.ground, g_pBuckbeakMinigame->camera);

    if (distance <= 0x1F40000)
    {
        GetOffsetFromPoint(pPoint->world.ground, &g_pBuckbeakMinigame->camera, &offset);
        RotateBuckbeakMinigameOffset(offset, -g_pBuckbeakMinigame->dwHeading.parts.wWhole, &offset);
        offset.x = -offset.x;
        offset.y = -offset.y;

        if ((u32)(offset.y - 0x50001) > 0x1EEFFFE)
        {
            pPoint->screen.xy.x = 0x780000;
        }
        else
        {
            x = offset.x;
            if (x < 0)
                x = -x;
            limit = FixedMultiply(0x15555, offset.y);
            if (limit < 0)
                limit = -limit;

            if (x <= limit)
            {
                scale = FixedDivide(0xA50000, offset.y);
                pPoint->dwScale = scale;
                pPoint->screen.xy.x = FixedMultiply(offset.x, -scale);
                y = FixedMultiply(0x451E,
                                  FixedMultiply(pPoint->world.dwHeight - g_pBuckbeakMinigame->dwCameraHeight.dwValue,
                                                -scale));
                pPoint->screen.xy.y = y;

                if (y <= 0xA60000)
                {
                    pPoint->screen.dwDepth = offset.y;
                    pPoint->screen.xy.x += 0x780000;
                    pPoint->screen.xy.y = y + 0x3B0000;
                    return 1;
                }
            }
        }
    }

    pPoint->screen.dwDepth = 0x1F40001;
    return 0;
}
