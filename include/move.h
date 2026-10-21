#pragma once

#include "types.h"
#include "actor.h"

// Pixel edges of an actor's terrain box (Actor.bTerrainBox*) around its integer position.
typedef struct TerrainBox {
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
} TerrainBox;

// A line from (x0, y0) to (x1, y1) in an 8x8-pixel terrain cell.
typedef struct SlopeLineSegment {
    u8 x0 : 4;
    u8 y0 : 4;
    u8 x1 : 4;
    u8 y1 : 4;
} __attribute__((packed)) SlopeLineSegment;

// A pixel coordinate in room space, passed by value.
typedef struct PixelPoint {
    u32 x;
    u32 y;
} PixelPoint;

// A signed x/y offset or step, passed by value. Also carries 16.16 deltas for TryNudgeActor.
typedef struct PixelVector {
    s32 x;
    s32 y;
} PixelVector;

// The pattern id is the low 12 bits of a collision tilemap entry.
#define COLLISION_BLOCK_PATTERN_ID(entry) ((u32)(entry) << 20 >> 20)

// Terrain types at the far and near end of the first edge ScanTerrainEdge samples for an actor;
// ResolveActorTerrain sets [0] to 0xFF to mark them as not yet sampled.
extern u32 g_adwEdgeEndpointTypes[2];
extern u8 *g_pRoomCollisionBehaviorTable;
extern u8 *g_pRoomCollisionTilemapBuffer;
extern u16 *g_pRoomCollisionTilemap;
extern u32 g_dwRoomCollisionPatternCount;

// ROM 0x08066094 (US): the facing opposite to each of the eight facings.
extern const u8 g_abOppositeFacing[8];
// ROM 0x0806609C (US): a tile's four edges, indexed by facing / 2.
extern const SlopeLineSegment g_aTileEdgeSegments[4];
// ROM 0x080660A4 (US): terrain types 2-25.
extern const SlopeLineSegment g_aSlopeLineSegments[24];

extern void ResolveActorTerrain(Actor *actor);  // 0x0802D704
extern u32 GetActorTerrainType(Actor *actor, TerrainBox *box);  // 0x0802D868
extern u32 ApplyTerrainTypeEffect(Actor *actor, TerrainBox *box, u32 type);  // 0x0802D8F4
extern void RespondToTerrain(Actor *actor, u32 type);  // 0x0802DA20
extern u32 TrySlideAlongSlope(Actor *actor, u32 type);  // 0x0802DB20
extern u32 ScanTerrainEdge(u32 direction, TerrainBox *box);  // 0x0802DC3C
extern u32 NudgeAlongVelocity(Actor *actor, PixelVector delta);  // 0x0802DF74
extern u32 TryNudgeActor(Actor *actor, PixelVector delta);  // 0x0802DFB4
extern u32 GetCollisionLayerAtPixel(PixelPoint pixel);  // 0x0802E030
extern void SetRoomCollisionPattern(u16 x, u16 y, u16 patternId);  // 0x0802DDD4
extern u16 GetRoomCollisionPattern(u16 x, u16 y);  // 0x0802DE00
extern void ReverseActorDirection(Actor *actor);  // 0x0802DE28
extern u8 StartMoveVelocity(Actor *actor);  // 0x0802DE68
extern void GetActorTerrainBox(Actor *actor, TerrainBox *box);  // 0x0802DEE0
extern u32 IsBlockingCollisionType(u32 type);  // 0x0802DF28, nonzero for types 1-25
extern u32 GetCollisionTypeAtPixel_candidate(PixelPoint pixel);  // 0x0802D7A0
extern void NoopInit2(void);
extern void LoadRoomSharedTileset_candidate(const void *pCollisionBehaviorTable, const void *pCollisionTilemap);
// Called by ExitOverworldScreen.
extern void FreeRoomSharedTileset(void);
extern void ApplyRoomSwitchEffect(u32 state);
// Field spell effects. The effect actor keeps its FieldSpell in wCharacterId_candidate and the
// caster in pLinkedActor_candidate; its collision callbacks run the spell on what it touches.
extern Actor *SpawnFieldSpellEffect(Actor *caster, u8 spell);
extern void HandleFieldSpellHit(Actor *effect, Actor *target);
extern void HandleFieldSpellSecondaryHit(Actor *effect, Actor *target);
extern void EndFieldSpellEffect(Actor *effect);  // pfnDestructor of the effect actor
extern void TickFieldSpellEffect(Actor *effect);
extern void TickDiffindoEffect(Actor *effect);
extern void TickGlaciusEffect(Actor *effect);
extern void TickSpongifyEffect(Actor *effect);
extern void InitReparoParticleEmitter(ParticleEmitter *emitter);
extern void InitGlaciusParticleEmitter(ParticleEmitter *emitter, Actor *effect);
extern void InitSpongifyParticleEmitter0(ParticleEmitter *emitter, Actor *effect);
extern void InitSpongifyParticleEmitter1(ParticleEmitter *emitter, Actor *effect);
extern void TickFieldSpellCompanionActor(Actor *companion);
extern void PlayFieldSpellHitSound(Actor *effect);

extern u32 g_dwFieldSpellActive;
extern Actor *g_pFieldSpellEffectActor;
extern Actor *g_pFieldSpellCompanionActor;
extern s32 g_nLumosScale;

// ROM 0x080660D4 (US): field spell effect sprites and animations, see
// src/move/field_spell_effects.globals.c.
extern const ActorAssetRecord g_aFieldSpellCastAssets[8];
extern const ActorAssetRecord g_aFieldSpellAssets[8];
extern const ActorAssetRecord g_aFieldSpellCompanionAssets[8];
extern const ActorGfxRecord g_LumosParticleGfx;
extern const ActorGfxRecord g_ReparoParticleGfx0;
extern const ActorGfxRecord g_ReparoParticleGfx1;
extern const ActorGfxRecord g_ReparoParticleGfx2;
extern const ActorGfxRecord g_GlaciusParticleGfx;
extern const ActorGfxRecord g_SpongifyParticleGfx0;
extern const ActorGfxRecord g_SpongifyParticleGfx1;
extern const ActorGfxRecord g_LumosPlayerGfx;
extern const ActorGfxRecord g_LumosEndPlayerGfx;
extern const u8 g_abLumosPlayerStandFrames[8];
extern const u8 g_abFacingDirection4[8];
extern const u8 g_aaFieldSpellCastAnims[8][66];
extern const u8 g_aaFieldSpellCompanionAnims[8][66];
extern const u8 g_aaFieldSpellAnims[8][66];
extern const u8 g_aaFieldSpellFlightAnims[8][66];
extern const u8 g_aaFieldSpellImpactAnims[4][66];
extern const u8 g_aaAlohomoraUnlockAnims[4][66];
extern const u8 g_abDiffindoEndAnim[66];
extern const u8 g_abDiffindoHitAnim[66];
extern const u8 g_abSpongifyHitAnim[66];
extern const u8 g_abSpongifyEndAnim[66];
extern const PixelVector g_aFieldSpellVelocities[8];
