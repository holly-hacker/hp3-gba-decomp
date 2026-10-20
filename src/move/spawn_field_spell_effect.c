#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "palette.h"
#include "particles.h"
#include "sound.h"

// Spawns the effect actor of field spell `spell` at the caster's anchor 0. Glacius, Spongify
// and Diffindo fly off in the caster's facing with their own pfnTick.
Actor *SpawnFieldSpellEffect(Actor *caster, u8 spell)
{
    Actor *effect;
    FixedPoint anchor;

    effect = AllocActorOfType(0xF);
    effect->oam.priority = 1;
    effect->bDepthSortBias = 0;
    GetActorAnchorPosition(caster, 0, &anchor);
    SnapActorPosition(effect, anchor.x, anchor.y);
    effect->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation | ActorFlagUnk2000
                      | ActorFlagTerrainDrawLayer;
    effect->nMoveSpeed = 1;
    effect->wCharacterId_candidate = spell;
    effect->anim.bAnimFrameDelay = 1;
    effect->pfnTick = TickFieldSpellEffect;
    effect->pfnDestructor = EndFieldSpellEffect;
    effect->apfnCollisionCallback[0] = HandleFieldSpellHit;
    effect->apfnCollisionCallback[1] = HandleFieldSpellSecondaryHit;
    AttachActorPalette(effect, g_aFieldSpellCastAssets[spell].pPalette);
    SetActorAnimData(effect, &g_aFieldSpellCastAssets[spell], g_aaFieldSpellCastAnims[spell], 0);
    SetActorActionSubState(effect, 0);
    g_dwFieldSpellActive = 1;
    effect->pLinkedActor_candidate = caster;
    effect->bFighterIndex = 0;
    effect->timer84.nFlightTicks = 45;

    switch (spell)
    {
    case FieldSpellFlipendo:
        PlaySoundById(0x10);
        break;
    case FieldSpellReparo:
        PlaySoundById(0x49);
        LoadParticleGfx(2, 0, (const ActorAssetRecord *)&g_ReparoParticleGfx0);
        LoadParticleGfx(2, 1, (const ActorAssetRecord *)&g_ReparoParticleGfx1);
        LoadParticleGfx(2, 2, (const ActorAssetRecord *)&g_ReparoParticleGfx2);
        break;
    case FieldSpellAlohomora:
    case FieldSpellWingardiumLeviosa:
        PlaySoundById(0x49);
        break;
    case FieldSpellLumos:
        LoadParticleGfx(2, 0, (const ActorAssetRecord *)&g_LumosParticleGfx);
        PlaySoundById(0x4F);
        break;
    case FieldSpellGlacius:
        LoadParticleGfx(2, 4, (const ActorAssetRecord *)&g_GlaciusParticleGfx);
        effect->bUnk_0x7C = 4;
        effect->pfnTick = TickGlaciusEffect;
        effect->nMoveSpeed = 0x38000;
        effect->bFacing = caster->bFacing;
        PlaySoundById(0x57);
        break;
    case FieldSpellSpongify:
        LoadParticleGfx(2, 0, (const ActorAssetRecord *)&g_SpongifyParticleGfx0);
        LoadParticleGfx(2, 1, (const ActorAssetRecord *)&g_SpongifyParticleGfx1);
        effect->bUnk_0x7C = 4;
        effect->pfnTick = TickSpongifyEffect;
        effect->nMoveSpeed = 0x38000;
        effect->bFacing = caster->bFacing;
        PlaySoundById(0x56);
        break;
    case FieldSpellDiffindo:
        effect->bUnk_0x7C = 4;
        PlaySoundById(0x53);
        effect->pfnTick = TickDiffindoEffect;
        effect->nMoveSpeed = 0x38000;
        effect->bFacing = caster->bFacing;
        break;
    }

    g_pFieldSpellEffectActor = effect;
    return effect;
}
