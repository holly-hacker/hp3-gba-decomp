#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// Plays animation `state` on a monster's Actor (wActorType is the monster id + 4), and
// on its companion shadow Actor for monsters 45-47. State 0 (idle) starts
// from one of 2 random frames.
void SetMonsterActorAnim(Actor *actor, u8 state)
{
    if (actor->dwFlags & ActorFlagVisible) {
        actor->dwFlags &= ~(ActorFlagVisible | ActorFlagActionAnimDone);
        SetActorAnimData(actor, &g_pMonsterGraphicsTable[actor->wActorType - 4].battle,
                          g_pMonsterAnimFrameTable[actor->wActorType - 4], state);

        if ((u16)(actor->wActorType - 0x31) <= 2) {
            SetActorAnimData(actor->pShadowActor, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
        } else if (state == 0) {
            actor->anim.pAnimFrameCursor += Mt19937RandMax(2) * 4;
            SetActorAnimFrame(actor, *actor->anim.pAnimFrameCursor);
        }

        actor->dwFlags |= ActorFlagVisible;
    } else {
        actor->dwFlags &= ~ActorFlagActionAnimDone;
        SetActorAnimData(actor, &g_pMonsterGraphicsTable[actor->wActorType - 4].battle,
                          g_pMonsterAnimFrameTable[actor->wActorType - 4], state);

        if ((u16)(actor->wActorType - 0x31) <= 2)
            SetActorAnimData(actor->pShadowActor, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
    }
}
