#include "types.h"
#include "combat_dialog.h"
#include "combat_fx.h"
#include "combat_fighter.h"

s32 TryApplyParalysis(BattleFighter *fighter, s32 isEnemyMonster, s32 escapeChance)
{
    if ((g_effectStaging.wContextValue == 0 || g_effectStaging.wContextValue == 1001)
        && isEnemyMonster == 0)
        return 0;

    if (!(fighter->bStatusFlags & 0x90))
    {
        fighter->pActor->wActionVariant = 2;
        fighter->bStatusFlags |= Paralyzed;
        fighter->bParalysisEscapeChance = escapeChance;
        fighter->pActor->anim.bAnimFrameCounter = 0;
        if (IS_SALAMANDER(fighter->pActor->wActorType - 4))
            fighter->pActor->pShadowActor->anim.bAnimFrameCounter = 0;
        return 1;
    }

    if (isEnemyMonster)
        ShowBattleMessage(ImmuneToParalysis, 0, g_effectStaging.bTargetIndex);
    return 0;
}
