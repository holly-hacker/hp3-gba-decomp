#include "types.h"
#include "overworld/room.h"

// Shows the animation's current step, then advances it. Each block's tiles on the
// frame's BG layers (and its collision pattern, if requested) are copied to the
// animation's position, offset by the block's distance from the frame's first block.
void ApplyRoomTileAnimationFrame(RoomTileAnimation *pAnim)
{
    u16 originX;
    u16 originY;
    u16 x;
    u16 y;
    u32 blockCount;
    u32 layerMask;
    u32 i;
    u32 layer;
    s32 dx;
    s32 dy;
    u32 value;

    pAnim->bDelay = GetRoomTileAnimFrameDelay(pAnim);
    blockCount = GetRoomTileAnimFrameBlockCount(pAnim);
    layerMask = GetRoomTileAnimFrameLayerMask(pAnim);

    if (pAnim->bDelay == ROOM_TILE_ANIM_LOOP)
    {
        pAnim->bStep = 0;
        pAnim->bDelay = GetRoomTileAnimFrameDelay(pAnim);
        ApplyRoomTileAnimationFrame(pAnim);
    }
    else if (pAnim->bDelay == ROOM_TILE_ANIM_HALT)
    {
        pAnim->bFlags |= 1;
    }
    else
    {
        GetRoomTileAnimFrameBlockPos(pAnim, 0, &originX, &originY);

        for (i = 0; i < blockCount; i++)
        {
            GetRoomTileAnimFrameBlockPos(pAnim, i, &x, &y);
            dx = x - originX;
            dy = y - originY;

            for (layer = 0; layer < ROOM_TILE_ANIM_COLLISION_LAYER; layer++)
            {
                if (layerMask & (1 << layer))
                {
                    value = GetRoomBgBlockEntry(x, y, layer);
                    WriteRoomBgTile_candidate(pAnim->wX + dx, pAnim->wY + dy, value, layer);
                }
            }

            if (layerMask & (1 << layer))
            {
                value = GetRoomCollisionPattern(x, y);
                SetRoomCollisionPattern(pAnim->wX + dx, pAnim->wY + dy, value);
            }
        }

        pAnim->bStep++;
    }
}
