#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// Plays animation `state` on a monster's Actor (wActorType is the monster id + 4), and
// on its companion shadow Actor for monsters 45-47. State 0 (idle) starts
// from one of 2 random frames.
void SetMonsterObjectAnim(Actor *obj, u8 state)
{
    if (obj->dwFlags & ActorFlagVisible) {
        obj->dwFlags &= ~(ActorFlagVisible | ActorFlagActionAnimDone);
        SetActorAnimData(obj, &g_pMonsterGraphicsTable[obj->wActorType - 4].battle,
                          g_pMonsterAnimFrameTable[obj->wActorType - 4], state);

        if ((u16)(obj->wActorType - 0x31) <= 2) {
            SetActorAnimData(obj->pShadowActor, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
        } else if (state == 0) {
            obj->anim.pAnimFrameCursor += Mt19937RandMax(2) * 4;
            SetActorAnimFrame(obj, *obj->anim.pAnimFrameCursor);
        }

        obj->dwFlags |= ActorFlagVisible;
    } else {
        obj->dwFlags &= ~ActorFlagActionAnimDone;
        SetActorAnimData(obj, &g_pMonsterGraphicsTable[obj->wActorType - 4].battle,
                          g_pMonsterAnimFrameTable[obj->wActorType - 4], state);

        if ((u16)(obj->wActorType - 0x31) <= 2)
            SetActorAnimData(obj->pShadowActor, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
    }
}
