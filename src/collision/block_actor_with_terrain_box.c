#include "types.h"
#include "actor.h"
#include "math.h"
#include "collision.h"

// Keeps pOther's pending move out of pSelf's terrain box. Two points on the
// leading edge of pOther's box, chosen by its facing, are tested against the
// box: a diagonal mover loses the blocked axis, a straight mover is nudged
// sideways by an eighth of its speed to slide around a corner, and a mover
// that already overlaps the box without either point inside it is stopped.
void BlockActorWithTerrainBox(Actor *pSelf, Actor *pOther)
{
    FixedPoint push;
    FixedPoint pos;
    s32 selfTop;
    s32 selfLeft;
    s32 selfBottom;
    s32 selfRight;
    s32 top;
    s32 left;
    s32 bottom;
    s32 right;
    IntPoint probe1;
    IntPoint probe2;
    s32 hit1;
    s32 hit2;
    s32 facing;

    pos = pSelf->posPrev;
    selfTop = (pos.y >> 16) + pSelf->bTerrainBoxTop;
    selfBottom = (pos.y >> 16) + pSelf->bTerrainBoxBottom;
    if (pSelf->oam.hFlip)
    {
        selfLeft = (pos.x >> 16) - pSelf->bTerrainBoxRight;
        selfRight = (pos.x >> 16) - pSelf->bTerrainBoxLeft;
    }
    else
    {
        selfLeft = (pos.x >> 16) + pSelf->bTerrainBoxLeft;
        selfRight = (pos.x >> 16) + pSelf->bTerrainBoxRight;
    }

    pos = pOther->posPrev;
    top = (pos.y >> 16) + pOther->bTerrainBoxTop;
    bottom = (pos.y >> 16) + pOther->bTerrainBoxBottom;
    if (pOther->oam.hFlip)
    {
        left = (pos.x >> 16) - pOther->bTerrainBoxRight;
        right = (pos.x >> 16) - pOther->bTerrainBoxLeft;
    }
    else
    {
        left = (pos.x >> 16) + pOther->bTerrainBoxLeft;
        right = (pos.x >> 16) + pOther->bTerrainBoxRight;
    }

    // A diagonal tests the middle of its vertical edge (probe1) and of its
    // horizontal edge (probe2); a straight facing tests both leading corners.
    facing = pOther->bFacing;
    switch (facing)
    {
    case DirectionUp:
        probe1.x = left;
        probe1.y = top;
        probe2.x = right;
        probe2.y = top;
        break;
    case DirectionUpRight:
        probe1.x = left + ((right - left) >> 1);
        probe1.y = top;
        probe2.x = right;
        probe2.y = top + ((bottom - top) >> 1);
        break;
    case DirectionRight:
        probe1.x = right;
        probe1.y = top;
        probe2.x = right;
        probe2.y = bottom;
        break;
    case DirectionDownRight:
        probe1.x = left + ((right - left) >> 1);
        probe1.y = bottom;
        probe2.x = right;
        probe2.y = top + ((bottom - top) >> 1);
        break;
    case DirectionDown:
        probe1.x = left;
        probe1.y = bottom;
        probe2.x = right;
        probe2.y = bottom;
        break;
    case DirectionDownLeft:
        probe1.x = left + ((right - left) >> 1);
        probe1.y = bottom;
        probe2.x = left;
        probe2.y = top + ((bottom - top) >> 1);
        break;
    case DirectionLeft:
        probe1.x = left;
        probe1.y = top;
        probe2.x = left;
        probe2.y = bottom;
        break;
    case DirectionUpLeft:
        probe1.x = left + ((right - left) >> 1);
        probe1.y = top;
        probe2.x = left;
        probe2.y = top + ((bottom - top) >> 1);
        break;
    }

    hit1 = 0;
    if (probe1.x >= selfLeft && probe1.x <= selfRight && probe1.y >= selfTop
        && probe1.y <= selfBottom)
        hit1 = 1;
    hit2 = 0;
    if (probe2.x >= selfLeft && probe2.x <= selfRight && probe2.y >= selfTop
        && probe2.y <= selfBottom)
        hit2 = 1;

    if (hit1 || hit2)
    {
        if (facing & 1)
        {
            if (hit1)
                pOther->posPrev.y = pOther->pos.y;
            if (hit2)
                pOther->posPrev.x = pOther->pos.x;
        }
        else
        {
            push.x = 0;
            push.y = 0;
            if (hit1)
            {
                if (facing == DirectionUp || facing == DirectionDown)
                    push.x = pOther->nMoveSpeed >> 3;
                else
                    push.y = pOther->nMoveSpeed >> 3;
                AddOffsetToPointInto(pOther->pos, &push, &pOther->posPrev);
            }
            if (hit2)
            {
                if (facing == DirectionUp || facing == DirectionDown)
                    push.x = -pOther->nMoveSpeed >> 3;
                else
                    push.y = -pOther->nMoveSpeed >> 3;
                AddOffsetToPointInto(pOther->pos, &push, &pOther->posPrev);
            }
            if (hit1 && hit2)
                pOther->posPrev = pOther->pos;
        }
    }
    else
    {
        // hit1 now records whether the two boxes overlap.
        hit1 = 1;
        if (selfRight < left)
            hit1 = 0;
        else if (selfLeft > right)
            hit1 = 0;
        else if (selfTop > bottom)
            hit1 = 0;
        else if (selfBottom < top)
            hit1 = 0;

        if (hit1 == 1)
        {
            pOther->posPrev = pOther->pos;
            pOther->vel.x = pOther->vel.y = 0;
        }
    }
}
