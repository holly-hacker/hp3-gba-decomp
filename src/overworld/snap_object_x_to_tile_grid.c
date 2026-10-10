#include "types.h"
#include "graphics/object.h"

// Stops an object that has come to rest on a tile and moves it horizontally so
// the left edge of its terrain box lies on the nearest 8-pixel column.
void SnapObjectXToTileGrid(Object *obj)
{
    s32 posX;
    u32 fixedX;
    u32 gridX;

    SetObjectActionSubState(obj, 12);
    obj->dwStateTimer = 8;
    obj->vel.x = 0;
    obj->vel.y = 0;

    posX = (s16)(obj->posPrev.x >> 16);
    fixedX = (obj->bTerrainBoxLeft + posX + 4) << 16;
    gridX = 0xFFF80000;
    gridX &= fixedX;
    SnapObjectPosition(obj, ((gridX >> 16) - obj->bTerrainBoxLeft) << 16, obj->pos.y);
}
