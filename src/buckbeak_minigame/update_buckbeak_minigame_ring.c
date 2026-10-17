#include "types.h"
#include "palette.h"
#include "buckbeak_minigame.h"
#include "math.h"
#include "gen/graphics/minigames/buckbeak.h"

// Places ring `index`'s three parts on screen and sizes them by distance, or hides
// them when the ring is out of view.
void UpdateBuckbeakMinigameRing(u32 index)
{
    BuckbeakMinigameRing *pRing = &g_pBuckbeakMinigame->aRings[index];
    s32 radius;
    u8 row;
    s32 j;

    pRing->bVisible = ProjectBuckbeakMinigamePoint(&pRing->point);

    if (pRing->bVisible)
    {
        radius = FixedMultiply(pRing->point.dwScale, 0xA0000) >> 16;
        row = GetBuckbeakMinigameRingFrameRow(pRing);

        for (j = 0; j < 3; j++)
        {
            pRing->apParts[j]->dwFlags |= ActorFlagVisible;
            SnapActorPosition(pRing->apParts[j], pRing->point.screen.xy.x, pRing->point.screen.xy.y);
            SetActorAnimFrame(pRing->apParts[j], row * 6 + pRing->apParts[j]->bFighterIndex);

            if (index == g_pBuckbeakMinigame->bNextRing)
            {
                if (pRing->bTargeted == 0)
                {
                    ReleaseActorPalette(pRing->apParts[j]);
                    AttachActorPalette(pRing->apParts[j], (const ObjPalette *)gBuckbeakMinigamePalette004Palette);
                }
            }
            else if (pRing->bTargeted != 0)
            {
                ReleaseActorPalette(pRing->apParts[j]);
                AttachActorPalette(pRing->apParts[j], (const ObjPalette *)gBuckbeakMinigamePalette003Palette);
            }

            if (--pRing->apParts[j]->dwStateTimer == 0)
            {
                pRing->apParts[j]->dwStateTimer = 3;
                pRing->apParts[j]->bFighterIndex++;
                if (pRing->apParts[j]->bFighterIndex > 5)
                    pRing->apParts[j]->bFighterIndex = 0;
            }

            SetActorOrbitRadii(pRing->apParts[j], radius, radius);
            pRing->apParts[j]->bDepthSortBias = 0x87 - row;
        }

        if (index == g_pBuckbeakMinigame->bNextRing)
        {
            if (pRing->bTargeted == 0)
                pRing->bTargeted = 1;
        }
        else if (pRing->bTargeted != 0)
            pRing->bTargeted = 0;
    }
    else
    {
        for (j = 0; j < 3; j++)
            pRing->apParts[j]->dwFlags &= ~ActorFlagVisible;
    }
}
