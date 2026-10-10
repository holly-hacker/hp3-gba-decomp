#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "gen/graphics/menus.h"

// Attaches the sparkle emitter to a menu cursor object (cursor kind 4 of SpawnMenuCursorObject).
// Mode 6 particles take their horizontal speed from Mt19937RandRange on the gameplay RNG
// cursor, and the emitter's spawn chance is rolled on the visual cursor.
void CreateMenuCursorEmitter(Object *pCursor)
{
    ParticleEmitter *emitter;

    emitter = AllocParticleEmitter((const ObjPalette *)gMenuCursorSparklePalette, 0, 0);
    emitter->pTarget = pCursor;
    emitter->wSpawnPeriod = 5;
    emitter->wLifetimeBase = 0x23;
    emitter->wLifetimeRange = 5;
    emitter->wFlags = 0xC84;
    emitter->wSpread = 1;
    emitter->wSpawnTimer = 0;
    emitter->bMode = 6;
    emitter->bSpawnsPerPeriod = 1;
    emitter->bOamSize = 0;
    emitter->bParam43 = 0;
    emitter->bAnimTicks = 2;
    emitter->abVelRange[0] = -40;
    emitter->abVelRange[1] = 40;
    emitter->abVelRange[2] = 0;
    emitter->abVelRange[3] = 0;
    emitter->wParam38 = 0x200;
    emitter->wSpawnRollMax = 0x1000;
    emitter->wSpawnRollThreshold = 0x800;
    g_pMenuCursorEmitter = emitter;
}
