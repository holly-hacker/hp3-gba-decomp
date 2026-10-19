#include "combat_fx.h"
#include "particles.h"

void SpawnParalysisEffect(Actor *actor)
{
    ParticleEmitter *effect;

    effect = CreateBattleEffectEmitter(actor, 7, 10, 16, 8, 3, 0, 0, 0, 0, 0xFE,
                                       0, 0, 10, 0, 0, 1);
    effect->bParalysisEffectFlag_candidate = 1;
}
