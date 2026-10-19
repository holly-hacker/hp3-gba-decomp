#include "types.h"
#include "menu_icon.h"
#include "actor.h"
#include "palette.h"
#include "pscreen_gamecube.h"

void SpawnGameCubeLinkIconActors(void)
{
    u32 i;
    Actor *pActor;

    for (i = 0; i < 3; i++)
    {
        pActor = SpawnMenuIconActor(i, 0);
        pActor->dwFlags |= ActorFlagKeepPaletteSlot | ActorFlagHasAnimation;
        SetActorPosition(pActor, g_aGameCubeLinkIconPositions[i].wX, g_aGameCubeLinkIconPositions[i].wY);
        AttachActorPalette(pActor, g_aGameCubeLinkIconAssets[i].pPalette);
        SetActorSprite(pActor, &g_aGameCubeLinkIconAssets[i]);
    }
}
