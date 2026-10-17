#include "types.h"
#include "actor.h"
#include "overworld/room.h"
#include "scroll.h"

s32 UpdateActorOnscreenFlags(Actor *actor)
{
    s32 position[2];
    ActorSpriteBounds bounds;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;

    if (actor->dwFlags & ActorFlagHasSpriteCells) {
        actor->dwFlags |= ActorFlagOnscreen | ActorFlagOnscreenForTileAlloc;
        return 1;
    }

    position[0] = (s16)(actor->pos.x >> 16);
    position[1] = (s16)(actor->pos.y >> 16);
    bounds = actor->spriteBounds;

    if (actor->oam.hFlip) {
        left = position[0] - (s16)bounds.words.packedX + 9;
        right = position[0] - (s16)(bounds.words.packedX >> 16) - 249;
    }
    else {
        left = position[0] + (s16)(bounds.words.packedX >> 16) + 9;
        right = position[0] + (s16)bounds.words.packedX - 249;
    }

    top = position[1] + (s16)bounds.words.packedY - 169;
    bottom = position[1] + (s16)(bounds.words.packedY >> 16) + 9;

    if (left < g_CameraPosition_candidate.nX || right > g_CameraPosition_candidate.nX ||
        bottom < g_CameraPosition_candidate.nY || top > g_CameraPosition_candidate.nY) {
        if (actor->bForceOnscreen_candidate != 1) {
            actor->dwFlags &= ~(ActorFlagOnscreen | ActorFlagOnscreenForTileAlloc);
            return 0;
        }
    }

    actor->dwFlags |= ActorFlagOnscreen | ActorFlagOnscreenForTileAlloc;
    return 1;
}
