#include "types.h"
#include "combat_fx.h"
#include "combat.h"

// Stages a battle effect script into g_effectStaging, spawns the effect
// actor, then clears the attacker's anim state in FightState. Returns the
// spawned actor; no call site uses the value. See docs/memory-map/battle.md.
Actor *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage)
{
    Actor *actor;

    g_effectStaging.bIdStaged_candidate = effectId;
    g_effectStaging.bSlotParam = slotParam;
    g_effectStaging.bScriptParam = selectedActionIndex;
    g_effectStaging.bCasterIndex = activeFighterIndex;
    g_effectStaging.bTargetIndex = targetIdx;
    g_effectStaging.wContextValue = damage;
    g_effectStaging.bStateA_candidate = 0;
    g_effectStaging.bStateB_candidate = 1;
    g_effectStaging.wTimer_candidate = 0;
    g_effectStaging.wTimerMax_candidate = 0x1f;
    actor = CreateEffectScriptActor(effectId, 1);
    g_pFightState->pAttackAnimActor_candidate = NULL;
    g_pFightState->bAttackAnimState_candidate = 0;
    return actor;
}
