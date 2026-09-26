#include "types.h"
#include "object.h"
#include "room.h"

s32 UpdateObjectOnscreenFlags(Object *obj)
{
    s32 position[2];
    ObjectSpriteBounds bounds;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;

    if (obj->dwFlags & ObjectFlagHasSpriteCells) {
        obj->dwFlags |= ObjectFlagOnscreen | ObjectFlagOnscreenForTileAlloc;
        return 1;
    }

    position[0] = (s16)(obj->nX >> 16);
    position[1] = (s16)(obj->nY >> 16);
    bounds = obj->spriteBounds;

    if (obj->oam.hFlip) {
        left = position[0] - (s16)bounds.packedX + 9;
        right = position[0] - (s16)(bounds.packedX >> 16) - 249;
    }
    else {
        left = position[0] + (s16)(bounds.packedX >> 16) + 9;
        right = position[0] + (s16)bounds.packedX - 249;
    }

    top = position[1] + (s16)bounds.packedY - 169;
    bottom = position[1] + (s16)(bounds.packedY >> 16) + 9;

    if (left < g_CameraPosition_candidate.nX || right > g_CameraPosition_candidate.nX ||
        bottom < g_CameraPosition_candidate.nY || top > g_CameraPosition_candidate.nY) {
        if (obj->bForceOnscreen_candidate != 1) {
            obj->dwFlags &= ~(ObjectFlagOnscreen | ObjectFlagOnscreenForTileAlloc);
            return 0;
        }
    }

    obj->dwFlags |= ObjectFlagOnscreen | ObjectFlagOnscreenForTileAlloc;
    return 1;
}
