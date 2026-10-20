#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"

s32 FighterHasShadowActor(u32 fighterIndex)
{
    u32 monsterId;

    // Monster actor types follow the four party FighterTypes.
    monsterId = g_pFightState->pFighters[fighterIndex].pActor->wActorType - 4;
    if (IS_SALAMANDER(monsterId))
        return 1;

    return 0;
}
