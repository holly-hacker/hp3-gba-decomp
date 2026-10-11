#include "types.h"
#include "actor.h"

// Stops an actor that has come to rest on a tile and moves it horizontally so
// the left edge of its terrain box lies on the nearest 8-pixel column.
void SnapActorXToTileGrid(Actor *actor)
{
    s32 posX;
    u32 fixedX;
    u32 gridX;

    SetActorActionSubState(actor, 12);
    actor->dwStateTimer = 8;
    actor->vel.x = 0;
    actor->vel.y = 0;

    posX = (s16)(actor->posPrev.x >> 16);
    fixedX = (actor->bTerrainBoxLeft + posX + 4) << 16;
    gridX = 0xFFF80000;
    gridX &= fixedX;
    SnapActorPosition(actor, ((gridX >> 16) - actor->bTerrainBoxLeft) << 16, actor->pos.y);
}
