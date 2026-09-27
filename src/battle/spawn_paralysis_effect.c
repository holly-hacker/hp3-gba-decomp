#include "types.h"
#include "battle.h"
#include "graphics.h"

extern ParticleEmitter *CreateBattleEffectEmitter_candidate(Object *obj, s32 a1, s32 a2, s32 a3,
                                                             s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                                                             s32 a9, s32 a10, s32 a11, s32 a12, s32 a13,
                                                             s32 a14, s32 a15, s32 a16);

void SpawnParalysisEffect(Object *obj)
{
    ParticleEmitter *effect;

    effect = CreateBattleEffectEmitter_candidate(obj, 7, 10, 16, 8, 3, 0, 0, 0, 0, 0xFE,
                                                 0, 0, 10, 0, 0, 1);
    effect->bParalysisEffectFlag_candidate = 1;
}
