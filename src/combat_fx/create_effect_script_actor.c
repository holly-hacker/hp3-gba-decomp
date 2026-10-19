#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"

// Spawns a battle effect actor that runs g_apEffectScripts[effectId]
// through InterpretActorScript. With attachPalette set, the effect's own
// palette is bound as well.
Actor *CreateEffectScriptActor(s32 effectId, s32 attachPalette)
{
    Actor *actor;
    IntPoint pos;

    actor = AllocActorOfType(BattleActorType_EffectScript);
    pos = ComputeEffectSpawnPosition();
    SetActorPosition(actor, pos.x, pos.y);
    actor->dwFlags = ActorFlagHasTickLogic | ActorFlagHasAnimation;
    actor->anim.bAnimFrameDelay = g_aEffectAnimAssets[effectId].bAnimFrameDelay;
    actor->oam.objMode = 0;
    actor->oam.bpp8 = 0;
    actor->oam.priority = 1;
    actor->bDepthSortBias = 0;
    SetActorAnimData(actor, &g_aEffectAnimAssets[effectId], g_aEffectAnimData_candidate[effectId], 0);
    actor->pfnTick = InterpretActorScript;
    actor->modeState.effect.bEffectId = effectId;
    if (attachPalette)
        AttachActorPalette(actor, g_aEffectAnimAssets[effectId].pPalette);
    g_pFightState->pFighters[g_effectStaging.bCasterIndex].pActor->scriptState.bytes.bAttackOutcomeState = 0;
    return actor;
}
