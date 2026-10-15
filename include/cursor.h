#pragma once

#include "types.h"
#include "actor.h"

extern ParticleEmitter *g_pMenuCursorEmitter;     // 0x030028C0
extern s32 g_nMenuCursorPaletteEffect;            // 0x030028C4, -1 = none
extern u32 g_dwMenuCursorParticleGfxLoaded;       // 0x030028C8

// Sprite of every cursor kind except 5, set before the kind's own setup.
extern const ActorAssetRecord g_MenuCursorAsset;
// 256-color sprite of kinds 0 and 1.
extern const ActorAssetRecord g_MenuCursor8bppAsset;
extern const ActorAssetRecord g_MenuCursorKind5Asset;
// Kind 4: the list cursor's animation and its sparkle particles' graphics.
extern const ActorAssetRecord g_MenuCursorSparkleAnimAsset;
extern const u8 g_MenuCursorSparkleAnimData[];
extern const ActorAssetRecord g_MenuCursorParticleAsset;

// Spawns a shared menu cursor sprite; kind selects its graphics and setup
// (4 the list cursor, 2 the quantity arrows, 0/1 dialog and choose-character screen).
extern Actor *SpawnMenuCursorActor(u32 kind);
extern void CreateMenuCursorEmitter(Actor *pCursor);
extern void ReleaseMenuCursor(Actor *pActor);
extern void SetMenuCursorPosition(Actor *pActor, s32 x, s32 y);  // SetActorPosition
extern void SetMenuCursorVisible(Actor *pActor, u32 visible);
// Queues the 8bpp cursor sprite's colors: color 0 of OBJ palette rows 3-15.
extern void LoadMenuCursor8bppColors(void);
