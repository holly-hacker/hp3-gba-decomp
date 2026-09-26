#include "types.h"
#include "object.h"
#include "room.h"

// Returns the eight-way direction from pos toward target, like
// GetDirectionToTarget, but checks the room terrain in front of the object's
// terrain box first. A blocked diagonal slides along the horizontal axis if
// that is open, otherwise along the vertical one. The horizontal-only moves
// compute a probe pixel that is never checked.
u8 GetUnblockedDirectionToTarget(Object *obj, FixedPoint pos, FixedPoint target, s32 tolerance)
{
    PixelPoint probe;
    u8 dir;

    if (pos.y > target.y + tolerance)
    {
        if (pos.x > target.x + tolerance)
        {
            dir = DirectionUpLeft;
            probe.x = ((pos.x - tolerance) >> 16) + obj->bTerrainBoxLeft - 1;
            probe.y = ((pos.y - tolerance) >> 16) + obj->bTerrainBoxTop - 1;
            if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
            {
                probe.y = (pos.y >> 16) + obj->bTerrainBoxTop
                    + (obj->bTerrainBoxBottom - obj->bTerrainBoxTop) / 2 - 1;
                if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
                    dir = DirectionUp;
                else
                    dir = DirectionLeft;
            }
        }
        else if (pos.x < target.x - tolerance)
        {
            dir = DirectionUpRight;
            probe.x = ((pos.x + tolerance) >> 16) + obj->bTerrainBoxRight + 1;
            probe.y = ((pos.y - tolerance) >> 16) + obj->bTerrainBoxTop - 1;
            if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
            {
                probe.y = (pos.y >> 16) + obj->bTerrainBoxTop
                    + (obj->bTerrainBoxBottom - obj->bTerrainBoxTop) / 2 - 1;
                if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
                    dir = DirectionUp;
                else
                    dir = DirectionRight;
            }
        }
        else
            dir = DirectionUp;
    }
    else if (pos.y < target.y - tolerance)
    {
        if (pos.x > target.x + tolerance)
        {
            dir = DirectionDownLeft;
            probe.x = ((pos.x - tolerance) >> 16) + obj->bTerrainBoxLeft - 1;
            probe.y = ((pos.y + tolerance) >> 16) + obj->bTerrainBoxBottom + 1;
            if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
            {
                probe.y = (pos.y >> 16) + obj->bTerrainBoxTop
                    + (obj->bTerrainBoxBottom - obj->bTerrainBoxTop) / 2 + 1;
                if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
                    dir = DirectionDown;
                else
                    dir = DirectionLeft;
            }
        }
        else if (pos.x < target.x - tolerance)
        {
            dir = DirectionDownRight;
            probe.x = ((pos.x + tolerance) >> 16) + obj->bTerrainBoxRight + 1;
            probe.y = ((pos.y + tolerance) >> 16) + obj->bTerrainBoxBottom + 1;
            if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
            {
                probe.y = (pos.y >> 16) + obj->bTerrainBoxTop
                    + (obj->bTerrainBoxBottom - obj->bTerrainBoxTop) / 2 + 1;
                if (IsBlockingCollisionType(GetCollisionTypeAtPixel_candidate(probe)))
                    dir = DirectionDown;
                else
                    dir = DirectionRight;
            }
        }
        else
            dir = DirectionDown;
    }
    else
    {
        if (pos.x > target.x + tolerance)
        {
            dir = DirectionLeft;
            probe.x = ((pos.x - tolerance) >> 16) + obj->bTerrainBoxLeft - 1;
        }
        else if (pos.x < target.x - tolerance)
        {
            dir = DirectionRight;
            probe.x = ((pos.x + tolerance) >> 16) + obj->bTerrainBoxRight + 1;
        }
        else
            dir = DirectionAtTarget;
    }
    return dir;
}
