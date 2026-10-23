#include "types.h"
#include "actor.h"
#include "background.h"
#include "hero.h"
#include "map.h"
#include "move.h"
#include "palette.h"
#include "particles.h"
#include "hw/io_regs.h"
#include "gen/graphics/overworld.h"

// pfnTick of a field spell effect actor. Sub-state 0 waits for the cast animation, then starts
// the spell: Flipendo, Reparo and Alohomora fly off in the caster's facing, Lumos lights the
// room through the OBJ window and spawns its glow companion. Afterwards dwStateTimer counts
// the spell down to EndFieldSpellEffect.
void TickFieldSpellEffect(Actor *effect)
{
    u8 spell = effect->wSubtype;
    ParticleEmitter *emitter;
    IntPoint anchor;

    if ((effect->dwFlags & (ActorFlagWantsCollisionCheck | ActorFlagOnscreen)) == ActorFlagWantsCollisionCheck)
    {
        EndFieldSpellEffect(effect);
        return;
    }

    if (effect->bActionSubState == 0)
    {
        if (!(effect->dwFlags & ActorFlagActionAnimDone))
            return;

        SetActorActionSubState(effect, 1);
        effect->dwFlags &= ~ActorFlagActionAnimDone;
        if (g_aFieldSpellAssets[spell].pPalette != NULL)
        {
            ReleaseActorPalette(effect);
            AttachActorPalette(effect, g_aFieldSpellCastAssets[spell].pPalette);
        }
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);

        switch (spell)
        {
        case FieldSpellWingardiumLeviosa:
            effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision;
            effect->bTerrainBlockResponse = TerrainBlockEndFlight;
            SetActorActionState(effect, 0xF);
            effect->bFacing = effect->pLinkedActor->bFacing;
            effect->vel.x = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].x << 16;
            effect->vel.y = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].y << 16;
            effect->dwStateTimer = 30;
            break;
        case FieldSpellFlipendo:
        case FieldSpellAlohomora:
            SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                             g_aaFieldSpellFlightAnims[effect->pLinkedActor->bFacing], 0);
            effect->oam.hFlip = effect->pLinkedActor->bFacing > DirectionDown;
            effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision;
            effect->bTerrainBlockResponse = TerrainBlockEndFlight;
            SetActorActionState(effect, 0xF);
            effect->bFacing = effect->pLinkedActor->bFacing;
            effect->vel.x = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].x << 16;
            effect->vel.y = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].y << 16;
            effect->dwStateTimer = 30;
            break;
        case FieldSpellReparo:
            SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                             g_aaFieldSpellFlightAnims[effect->pLinkedActor->bFacing], 0);
            effect->oam.hFlip = effect->pLinkedActor->bFacing > DirectionDown;
            effect->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision;
            effect->bTerrainBlockResponse = TerrainBlockEndFlight;
            SetActorActionState(effect, 0xF);
            effect->bFacing = effect->pLinkedActor->bFacing;
            effect->vel.x = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].x << 16;
            effect->vel.y = g_aFieldSpellVelocities[effect->pLinkedActor->bFacing].y << 16;
            effect->dwStateTimer = 30;
            emitter = AllocParticleEmitter((const ObjPalette *)gReparoEffectPalette, 2, 0);
            emitter->pTarget = effect;
            InitReparoParticleEmitter(emitter);
            emitter = AllocParticleEmitter((const ObjPalette *)gReparoEffectPalette, 2, 1);
            emitter->pTarget = effect;
            InitReparoParticleEmitter(emitter);
            emitter = AllocParticleEmitter((const ObjPalette *)gReparoEffectPalette, 2, 2);
            emitter->pTarget = effect;
            InitReparoParticleEmitter(emitter);
            break;
        case FieldSpellLumos:
            if (g_dwRoomUsesBg0 != 0)
                effect->dwFlags &= ~ActorFlagVisible;
            else
            {
                effect->dwFlags |= ActorFlagVisible;
                REG_DISPCNT |= 0x8000;
                REG_WINOUT = 0x3F3E;
                EnableBg(0);
            }
            effect->dwStateTimer = 160;
            effect->oam.objMode = 2;
            g_nLumosScale = 0x8000;
            SetActorAffineTransform(effect, 0x8000, 0x8000, 0, 1);

            g_pPlayerActor->dwFlags &= ~ActorFlagVisible;
            SetActorAssetRecord(g_pPlayerActor, &g_LumosPlayerGfx);
            SetActorAnimFrame(g_pPlayerActor, g_abLumosPlayerStandFrames[g_pPlayerActor->bFacing]);
            g_pPlayerActor->dwFlags |= ActorFlagVisible;

            g_pFieldSpellCompanionActor = AllocActorOfType(RoomActorType_FieldSpellEffect);
            g_pFieldSpellCompanionActor->pLinkedActor = effect->pLinkedActor;
            GetActorFlippedAnchor(g_pFieldSpellCompanionActor->pLinkedActor, 0, &anchor);
            SnapActorPosition(g_pFieldSpellCompanionActor,
                              g_pFieldSpellCompanionActor->pLinkedActor->pos.x + (anchor.x << 16),
                              g_pFieldSpellCompanionActor->pLinkedActor->pos.y + (anchor.y << 16));
            g_pFieldSpellCompanionActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
                                                   | ActorFlagUnk2000;
            g_pFieldSpellCompanionActor->wSubtype = spell;
            g_pFieldSpellCompanionActor->anim.bAnimFrameDelay = 1;
            g_pFieldSpellCompanionActor->pfnTick = TickFieldSpellCompanionActor;
            AttachActorPalette(g_pFieldSpellCompanionActor, g_aFieldSpellCompanionAssets[spell].pPalette);
            SetActorAnimData(g_pFieldSpellCompanionActor, &g_aFieldSpellCompanionAssets[spell],
                             g_aaFieldSpellCompanionAnims[spell], 0);
            g_pFieldSpellCompanionActor->bFighterIndex = 0;

            emitter = AllocParticleEmitter((const ObjPalette *)gLumosCastPalette, 2, 0);
            emitter->pTarget = g_pFieldSpellCompanionActor;
            emitter->wSpawnPeriod = 5;
            emitter->wLifetimeBase = 20;
            emitter->wLifetimeRange = 5;
            emitter->wFlags = ParticleEmitterFlagPriorityBelow | ParticleEmitterFlagSpawnRoll
                              | ParticleEmitterFlagNoCollision | ParticleEmitterFlagAnimTicksFixed;
            emitter->wSpread = 1;
            emitter->wSpawnTimer = 0;
            emitter->bMode = ParticleModeRandomVelocity;
            emitter->bSpawnsPerPeriod = 1;
            emitter->bOamSize = 0;
            emitter->bParam43 = 0;
            emitter->bAnimTicks = 2;
            emitter->abVelRange[0] = 1;
            emitter->abVelRange[1] = 1;
            emitter->abVelRange[2] = 0;
            emitter->abVelRange[3] = 0;
            emitter->wParam38 = 0x200;
            emitter->wSpawnRollMax = 0x1000;
            emitter->wSpawnRollThreshold = 0x800;
            break;
        }
        return;
    }

    if (--effect->dwStateTimer == 0)
    {
        if (spell == FieldSpellAlohomora)
        {
            SetActorActionSubState(effect->pLinkedActor, 0xB);
            effect->pLinkedActor->dwFlags |= ActorFlagHasTickLogic;
            effect->pLinkedActor->dwStateTimer = 30;
        }
        EndFieldSpellEffect(effect);
    }

    if (spell == FieldSpellLumos)
    {
        if (effect->dwStateTimer > 150)
            g_nLumosScale += 0x2666;
        if (effect->dwStateTimer < 100)
            g_nLumosScale -= 0x3D7;
        if (effect->dwStateTimer == 20)
        {
            if (g_pPlayerActor->bTerrainType == 0x1F)
            {
                effect->dwStateTimer = 21;
                g_nLumosScale += 0x3D7;
            }
            else
            {
                g_pPlayerActor->bFighterIndex = 0;
                SetActorAnimData(g_pFieldSpellCompanionActor, &g_aFieldSpellCompanionAssets[spell],
                                 g_aaFieldSpellCompanionAnims[spell], 13);
                FreeAllParticleEmitters();
            }
        }
        if (effect->dwStateTimer == 14)
        {
            g_pFieldSpellCompanionActor->bFighterIndex = 1;
            effect->dwFlags &= ~ActorFlagVisible;
        }
        SetActorAffineTransform(effect, g_nLumosScale, g_nLumosScale, 0, 3);
    }

    if (spell == FieldSpellAlohomora && effect->dwStateTimer == 60)
    {
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                         g_aaAlohomoraUnlockAnims[g_abFacingDirection4[effect->pLinkedActor->bFacing]], 0);
        if (g_abFacingDirection4[effect->pLinkedActor->bFacing] == 3)
            effect->oam.hFlip = 1;
    }

    if (effect->dwStateTimer == 20 && effect->bFighterIndex == 1 && spell != FieldSpellLumos)
    {
        SetActorActionSubState(effect, 1);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
    }

    if (effect->bActionSubState == 5 && spell != FieldSpellLumos)
    {
        SetActorActionSubState(effect, 1);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
        effect->dwStateTimer = 20;
        PlayFieldSpellHitSound(effect);
    }

    if (effect != NULL)
    {
        switch (effect->wSubtype)
        {
        case FieldSpellLumos:
            SnapActorPosition(effect, effect->pLinkedActor->pos.x,
                              effect->pLinkedActor->pos.y - 0x100000);
            break;
        case FieldSpellFlipendo:
        case FieldSpellReparo:
        case FieldSpellAlohomora:
        case FieldSpellGlacius:
        case FieldSpellSpongify:
        case FieldSpellDiffindo:
            break;
        // HACK: without a break, the last case isn't merged with 2-6 into one range, which keeps the
        // case count high enough for the ROM's jump table.
        case FieldSpellWingardiumLeviosa:
            ;
        }
    }
}
