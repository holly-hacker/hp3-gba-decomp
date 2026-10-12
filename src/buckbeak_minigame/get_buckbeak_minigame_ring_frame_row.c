#include "types.h"
#include "math.h"
#include "buckbeak_minigame.h"

// Which of the seven ring sizes to draw for a ring's projected scale.
s32 GetBuckbeakMinigameRingFrameRow(BuckbeakMinigameRing *pRing)
{
    s32 row = (FixedMultiply(0x70000, pRing->point.dwScale) - 0x18000) >> 16;

    if (row > 6)
        row = 6;
    if (row < 0)
        row = 0;

    return row;
}
