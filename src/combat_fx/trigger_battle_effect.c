#include "types.h"
#include "combat_fx.h"
#include "combat.h"

// Stages a battle effect script into g_effectStaging, spawns the effect
// actor, then clears the attacker's anim state in FightState. Returns the
// spawned actor; no call site uses the value.
Actor *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage)
{
    Actor *actor;

    g_effectStaging.bEffectId = effectId;
    g_effectStaging.bSlotParam = slotParam;
    g_effectStaging.bScriptParam = selectedActionIndex;
    g_effectStaging.bCasterIndex = activeFighterIndex;
    g_effectStaging.bTargetIndex = targetIdx;
    g_effectStaging.wContextValue = damage;
    g_effectStaging.bBg0Priority = 0;
    g_effectStaging.bBg1Priority = 1;
    g_effectStaging.wBlendFirstTargets = 0;
    g_effectStaging.wBlendSecondTargets = 0x1f;
    actor = CreateEffectScriptActor(effectId, 1);
    g_pFightState->pAttackOutcomeActor = NULL;
    g_pFightState->bAttackOutcomeState = 0;
    return actor;
}
