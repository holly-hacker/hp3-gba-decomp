#include "types.h"
#include "actor.h"
#include "color.h"
#include "cursor.h"
#include "battle/effect_script.h"
#include "particles.h"

void ReleaseMenuCursor(Actor *pActor)
{
    if (pActor != NULL)
        pActor->dwFlags |= ActorFlagAnimFrameLoaded | ActorFlagPendingDestroy;

    if (g_pMenuCursorEmitter != NULL)
    {
        ReleaseParticleEmitter(g_pMenuCursorEmitter);
        g_pMenuCursorEmitter = NULL;
    }

    if (g_nMenuCursorPaletteEffect != -1)
    {
        StopPaletteEffect(g_nMenuCursorPaletteEffect);
        g_nMenuCursorPaletteEffect = -1;
    }

    if (g_dwMenuCursorParticleGfxLoaded)
    {
        g_dwMenuCursorParticleGfxLoaded = 0;
        sub_08031668(0, 0);
    }
}
