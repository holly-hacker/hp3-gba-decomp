#include "types.h"
#include "object.h"

// Returns the direction from pos toward target. An axis counts as aligned
// while pos is within tolerance of target on it. Four-way objects resolve
// diagonals to one axis: up-left to left, up-right to up, down-left to down,
// down-right to right.
u8 GetDirectionToTarget(u32 objectFlags, FixedPoint pos, FixedPoint target, s32 tolerance)
{
    u8 dir;

    if (objectFlags & ObjectFlagFourWayDirections_candidate)
    {
        if (pos.y > target.y + tolerance)
        {
            if (pos.x > target.x + tolerance)
                dir = Direction4Left;
            else
                dir = Direction4Up;
        }
        else if (pos.y < target.y - tolerance)
        {
            if (pos.x > target.x + tolerance)
                dir = Direction4Down;
            else if (pos.x < target.x - tolerance)
                dir = Direction4Right;
            else
                dir = Direction4Down;
        }
        else
        {
            if (pos.x > target.x + tolerance)
                dir = Direction4Left;
            else if (pos.x < target.x - tolerance)
                dir = Direction4Right;
            else
                dir = Direction4AtTarget;
        }
    }
    else
    {
        if (pos.y > target.y + tolerance)
        {
            if (pos.x > target.x + tolerance)
                dir = DirectionUpLeft;
            else if (pos.x < target.x - tolerance)
                dir = DirectionUpRight;
            else
                dir = DirectionUp;
        }
        else if (pos.y < target.y - tolerance)
        {
            if (pos.x > target.x + tolerance)
                dir = DirectionDownLeft;
            else if (pos.x < target.x - tolerance)
                dir = DirectionDownRight;
            else
                dir = DirectionDown;
        }
        else
        {
            if (pos.x > target.x + tolerance)
                dir = DirectionLeft;
            else if (pos.x < target.x - tolerance)
                dir = DirectionRight;
            else
                dir = DirectionAtTarget;
        }
    }
    return dir;
}
