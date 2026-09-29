#include "types.h"
#include "battle/battle.h"

s32 TryApplyParalysis(BattleFighter *fighter, s32 isEnemyMonster, s32 escapeChance)
{
    if ((g_effectStaging.wContextValue == 0 || g_effectStaging.wContextValue == 1001)
        && isEnemyMonster == 0)
        return 0;

    if (!(fighter->bStatusFlags & 0x90))
    {
        fighter->pObject->wActionVariant = 2;
        fighter->bStatusFlags |= Paralyzed;
        fighter->bParalysisEscapeChance = escapeChance;
        fighter->pObject->bAnimFrameCounter = 0;
        if ((u16)(fighter->pObject->wObjectType - 0x31) <= 2)
            fighter->pObject->pShadowObject->bAnimFrameCounter = 0;
        return 1;
    }

    if (isEnemyMonster)
        ShowBattleMessage(0x11, 0, g_effectStaging.bTargetIndex);
    return 0;
}
