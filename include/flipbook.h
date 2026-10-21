#pragma once

#include "types.h"
#include "actor.h"

// One animated room tile, stepped by TickRoomTileAnimations.
typedef struct RoomTileAnimation {
    u8 bSet;
    u8 bStep;
    u8 bDelay;
    u8 bFlags;
    u16 wX;
    u16 wY;
} RoomTileAnimation;

// RoomTileAnimation.bFlags: set by a ROOM_TILE_ANIM_HALT frame or HaltRoomTileAnimation.
#define ROOM_TILE_ANIM_FLAG_HALTED 1

#define MAX_ROOM_TILE_ANIMATIONS 32
extern RoomTileAnimation *g_aRoomTileAnimations;
extern u32 g_dwRoomTileAnimationCount;

// A 32x32-pixel room block, in block units.
typedef struct RoomTileAnimBlock {
    u16 wX;
    u16 wY;
} RoomTileAnimBlock;

// One step of a room tile animation: the blocks whose tiles are copied to the
// animation's position, offset from the first block. bDelay is the ticks until
// the next step (0 holds it); ROOM_TILE_ANIM_LOOP restarts the set and
// ROOM_TILE_ANIM_HALT pauses the animation (bFlags bit 0).
#define ROOM_TILE_ANIM_FRAME(blockCount) struct {                \
    u16 wBlockCount;                                             \
    u8 bDelay;                                                   \
    u8 bLayerMask;  /* bits 0-3: BG layers; bit 4: collision */  \
    RoomTileAnimBlock aBlocks[blockCount];                       \
}
typedef ROOM_TILE_ANIM_FRAME(0) RoomTileAnimFrame;

#define ROOM_TILE_ANIM_HALT 0xFE
#define ROOM_TILE_ANIM_LOOP 0xFF
#define ROOM_TILE_ANIM_COLLISION_LAYER 4

#define ROOM_TILE_ANIM_SET(frameCount) struct {  \
    u32 dwFrameCount;                            \
    const RoomTileAnimFrame *apFrames[frameCount]; \
}
typedef ROOM_TILE_ANIM_SET(0) RoomTileAnimSet;

// Indexed by RoomTileAnimation.bSet.
extern const RoomTileAnimSet *const g_apRoomTileAnimSets[55];

extern void AddRoomTileAnimation(u8 bSet, s32 x, s32 y, u8 bFlags);
extern void TickRoomTileAnimations(void);
extern void ApplyRoomTileAnimationFrame(RoomTileAnimation *pAnim);
extern void InitRoomTileAnimationTable(void);
extern void ClearRoomTileAnimations(void);
extern void ResumeRoomTileAnimation(s32 x, s32 y);
extern void HaltRoomTileAnimation(s32 x, s32 y);
extern void ApplyRoomTileAnimationAt(u8 bSet, u32 x, u32 y, u8 bFlags);
extern Actor *SpawnRoomTileAnimationActor_candidate(u8 bColumn, u8 bRow);
extern RoomTileAnimation *FindRoomTileAnimation(s32 x, s32 y);
extern u32 RewindRoomTileAnimationStep(RoomTileAnimation *pAnim);
extern u32 GetRoomTileAnimFrameBlockCount(const RoomTileAnimation *pAnim);
extern u32 GetRoomTileAnimFrameDelay(const RoomTileAnimation *pAnim);
extern u32 GetRoomTileAnimFrameLayerMask(const RoomTileAnimation *pAnim);
extern void GetRoomTileAnimFrameBlockPos(const RoomTileAnimation *pAnim, u32 index, u16 *pX, u16 *pY);
extern void TickRoomTileAnimationActor(Actor *pActor);
