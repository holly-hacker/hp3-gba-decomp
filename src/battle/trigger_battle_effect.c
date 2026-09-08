#include "types.h"
#include "battle.h"

// Stages a battle effect script into g_effectStaging, spawns the effect
// object, then clears the attacker's anim state in FightState. Returns the
// spawned object; no call site uses the value. See docs/memory-map/battle.md.
Object *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage)
{
    Object *obj;

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
    obj = CreateEffectScriptObject(effectId, 1);
    g_pFightState->pAttackAnimObject_candidate = NULL;
    g_pFightState->bAttackAnimState_candidate = 0;
    return obj;
}
