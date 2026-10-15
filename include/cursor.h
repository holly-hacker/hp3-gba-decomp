#pragma once

#include "types.h"
#include "actor.h"

extern ParticleEmitter *g_pMenuCursorEmitter;  // 0x030028C0

// Spawns a shared menu cursor sprite; kind selects its graphics and setup
// (4 the list cursor, 2 the quantity arrows, 0/1 dialog and choose-character screen).
extern Actor *SpawnMenuCursorActor(u32 kind);
extern void CreateMenuCursorEmitter(Actor *pCursor);
extern void ReleaseMenuCursor(Actor *pActor);
extern void SetMenuCursorPosition(Actor *pActor, s32 x, s32 y);  // SetActorPosition
