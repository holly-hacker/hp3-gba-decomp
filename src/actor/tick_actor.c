#include "types.h"
#include "actor.h"
#include "mem.h"
#include "sound.h"

// Runs one actor's per-frame update for TickActorList: frees it if marked for
// destruction, binds or releases its effect graphics by visibility, runs its
// pfnTick handler and movement/animation, and queues it for the collision,
// sprite-frame and OAM passes. mode == 1 is the full pass that also updates OAM.
void TickActor(Actor *actor, u32 mode)
{
    u32 flags;
    u32 posX;
    u32 posY;

    if (actor->dwFlags & ActorFlagPendingDestroy)
    {
        FreeActor(actor);
        return;
    }

    UpdateActorOnscreenFlags(actor);
    flags = actor->dwFlags;
    if (!(flags & ActorFlagKeepPaletteSlot))
    {
        if (flags & ActorFlagOnscreen)
            BindActorPendingPalette(actor);
        else
            ReleaseActorPalette(actor);
    }

    if (flags & (ActorFlagHasTickLogic | ActorFlagOnscreen))
    {
        if (actor->pfnTick != NULL && IsActorTickAllowed())
        {
            actor->pfnTick(actor);
            flags = actor->dwFlags;
        }

        if (flags & ActorFlagTickHandlerSuspendsMovement)
            return;

        if (IsActorTickAllowed())
        {
            if (actor->wMoveDuration != 0)
                TickActorMove(actor);
            TickActorAnimation(actor);
            if (actor->bAffineEffectTimer != 0)
                TickActorAffineEffect(actor);
            IntegrateActorVelocity(actor);
            CheckActorTerrainCollision(actor);
        }
        else
        {
            posX = actor->pos.x;
            posY = actor->pos.y;
            actor->posPrev.x = posX;
            actor->posPrev.y = posY;
        }

        if (IsActorTickAllowed()
            && (flags & (ActorFlagPendingDestroy | ActorFlagWantsCollisionCheck))
                == ActorFlagWantsCollisionCheck)
            g_apCollisionQueue[g_dwCollisionQueueCount++] = actor;

        if ((flags & (ActorFlagHasSpriteCells | ActorFlagVisible))
            == (ActorFlagHasSpriteCells | ActorFlagVisible))
            g_apSpriteFrameQueue[g_bSpriteFrameQueueCount++] = actor;

        if (g_dwUnk03003234 != 0)
        {
            g_dwUnk03003234 = 0;
            if (actor->pos.x != actor->posPrev.x || actor->pos.y != actor->posPrev.y)
                PlaySoundById(0x47);
        }
    }
    else
    {
        posX = actor->pos.x;
        posY = actor->pos.y;
        actor->posPrev.x = posX;
        actor->posPrev.y = posY;
    }

    if (mode == 1 && !(flags & ActorFlagOnscreenForTileAlloc))
        ReleaseActorOffscreenVramTiles(actor);

    if ((actor->dwFlags & (ActorFlagHasSpriteCells | ActorFlagOnscreen
                         | ActorFlagPendingDestroy | ActorFlagVisible))
        == (ActorFlagOnscreen | ActorFlagVisible))
        g_apOamQueue[g_dwOamQueueCount++] = actor;
}
