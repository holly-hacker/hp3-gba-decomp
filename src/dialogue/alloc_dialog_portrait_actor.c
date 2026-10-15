#include "types.h"
#include "actor.h"
#include "dialogue.h"

Actor *AllocDialogPortraitActor(void)
{
    Actor *actor;

    actor = AllocActorOfType(0xE);
    SetActorPosition(actor, 0, g_dwDialogBoxY + 0x28);
    actor->dwFlags = ActorFlagHasSpriteCells | ActorFlagHasAnimation | ActorFlagHasTickLogic;
    actor->anim.bAnimFrameDelay = 1;
    actor->pfnTick = NULL;
    actor->oam.objMode = 0;
    actor->oam.paletteNum = 1;
    actor->oam.bpp8 = 1;
    actor->oam.priority = 0;
    actor->bDepthSortBias = 0x80;
    return actor;
}
