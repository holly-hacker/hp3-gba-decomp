#include "types.h"
#include "math.h"
#include "buckbeak_minigame.h"

// Rotates an offset by angle (256 per turn).
void RotateBuckbeakMinigameOffset(FixedPoint offset, s32 angle, FixedPoint *pOut)
{
    s32 cosine = g_anSineTable[(angle + 0x40) & 0xFF];
    s32 sine = g_anSineTable[angle & 0xFF];
    s32 outX = FixedMultiply(offset.x, cosine) + FixedMultiply(offset.y, -sine);
    s32 outY = FixedMultiply(offset.x, sine) + FixedMultiply(offset.y, cosine);

    pOut->x = outX;
    pOut->y = outY;
}
