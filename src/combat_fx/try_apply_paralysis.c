#include "types.h"
#include "battle/battle.h"
#include "combat_dialog.h"
#include "combat_fx.h"

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
        if ((u16)(fighter->pActor->wActorType - 0x31) <= 2)
            fighter->pActor->pShadowActor->anim.bAnimFrameCounter = 0;
        return 1;
    }

    if (isEnemyMonster)
        ShowBattleMessage(0x11, 0, g_effectStaging.bTargetIndex);
    return 0;
}
