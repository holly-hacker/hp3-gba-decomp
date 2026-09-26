#include "types.h"
#include "object.h"
#include "mem.h"
#include "audio.h"

// Runs one object's per-frame update for TickObjectList: frees it if marked for
// destruction, binds or releases its effect graphics by visibility, runs its
// pfnTick handler and movement/animation, and queues it for the collision,
// sprite-frame and OAM passes. mode == 1 is the full pass that also updates OAM.
void TickObject(Object *obj, u32 mode)
{
    u32 flags;
    u32 posX;
    u32 posY;

    if (obj->dwFlags & ObjectFlagPendingDestroy)
    {
        FreeObject(obj);
        return;
    }

    UpdateObjectOnscreenFlags(obj);
    flags = obj->dwFlags;
    if (!(flags & ObjectFlagSuppressEffectBinding))
    {
        if (flags & ObjectFlagOnscreen)
            BindObjectEffectData(obj);
        else
            ReleaseObjectPalette(obj);
    }

    if (flags & (ObjectFlagHasTickLogic | ObjectFlagOnscreen))
    {
        if (obj->pfnTick != NULL && IsObjectTickAllowed())
        {
            obj->pfnTick(obj);
            flags = obj->dwFlags;
        }

        if (flags & ObjectFlagTickHandlerSuspendsMovement)
            return;

        if (IsObjectTickAllowed())
        {
            if (obj->wMoveDuration != 0)
                TickObjectMove(obj);
            TickObjectAnimation(obj);
            if (obj->bAffineEffectTimer != 0)
                TickObjectAffineEffect(obj);
            IntegrateObjectVelocity(obj);
            CheckObjectTerrainCollision(obj);
        }
        else
        {
            posX = obj->nX;
            posY = obj->nY;
            obj->nXPrev = posX;
            obj->nYPrev = posY;
        }

        if (IsObjectTickAllowed()
            && (flags & (ObjectFlagPendingDestroy | ObjectFlagWantsCollisionCheck))
                == ObjectFlagWantsCollisionCheck)
            g_apCollisionQueue[g_dwCollisionQueueCount++] = obj;

        if ((flags & (ObjectFlagHasSpriteCells | ObjectFlagVisible))
            == (ObjectFlagHasSpriteCells | ObjectFlagVisible))
            g_apSpriteFrameQueue[g_bSpriteFrameQueueCount++] = obj;

        if (g_dwUnk03003234 != 0)
        {
            g_dwUnk03003234 = 0;
            if (obj->nX != obj->nXPrev || obj->nY != obj->nYPrev)
                PlaySoundById(0x47);
        }
    }
    else
    {
        posX = obj->nX;
        posY = obj->nY;
        obj->nXPrev = posX;
        obj->nYPrev = posY;
    }

    if (mode == 1 && !(flags & ObjectFlagOnscreenForTileAlloc))
        ReleaseObjectOffscreenVramTiles(obj);

    if ((obj->dwFlags & (ObjectFlagHasSpriteCells | ObjectFlagOnscreen
                         | ObjectFlagPendingDestroy | ObjectFlagVisible))
        == (ObjectFlagOnscreen | ObjectFlagVisible))
        g_apOamQueue[g_dwOamQueueCount++] = obj;
}
