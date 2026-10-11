#include "types.h"
#include "actor.h"

// Returns 1 if the two actors' collision box 0 rects overlap; touching edges
// count as overlapping.
s32 DoActorsOverlap(Actor *a, Actor *b)
{
    ActorRect rectA;
    ActorRect rectB;

    rectA = GetActorCollisionBoxRect(a, 0);
    rectB = GetActorCollisionBoxRect(b, 0);

    if (rectA.right >= rectB.left && rectB.right >= rectA.left
        && rectA.bottom >= rectB.top && rectB.bottom >= rectA.top)
        return 1;
    return 0;
}
