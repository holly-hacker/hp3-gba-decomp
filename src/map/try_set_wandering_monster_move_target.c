#include "types.h"
#include "actor.h"
#include "move.h"
#include "map_inline.h"

// Sets the monster's move target unless the target pixel is off its kind's
// spawn terrain. Returns 1 when rejected, 0 when set.
u32 TrySetWanderingMonsterMoveTarget(Actor *pActor, s32 x, s32 y)
{
    if (GetCollisionTypeAtPixel((PixelPoint){ x >> 16, y >> 16 })
        == GetEncounterKindTerrainType(pActor->bReceivedRewardId))
    {
        SetActorMoveTarget(pActor, x, y);
        return 0;
    }

    return 1;
}
