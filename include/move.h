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
// ROM 0x080660A4 (US): terrain types 2-25, see docs/formats/collision.md.
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
extern u32 GetCollisionTypeAtPixel_candidate(PixelPoint pixel);  // 0x0802D7A0, see docs/formats/collision.md
extern void NoopInit2(void);
extern void LoadRoomSharedTileset_candidate(const void *pCollisionBehaviorTable, const void *pCollisionTilemap);
// Called by ExitOverworldScreen.
extern void FreeRoomSharedTileset(void);
extern void ApplyRoomSwitchEffect(u32 state);
// Spawns the effect actor of field spell `spell` (an Actor.bFighterIndex value) at
// the caster's anchor 0.
extern void SpawnFieldSpellEffect_candidate(Actor *caster, u8 spell);
extern void sub_0802E2BC(Actor *pSpell, Actor *pTarget);  // overworld spell effect hits a room actor

extern u32 g_dwPendingCameraFocusFlag;
extern void *g_pPendingCameraFocus_candidate;
extern void RestorePendingCameraFocus_candidate(void *pFocus);
