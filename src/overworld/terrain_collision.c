#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "hw/mem.h"
#include "divide.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/terrain.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SEGMENT_DX(segment) ((segment).x1 - (segment).x0)
#define SEGMENT_DY(segment) ((segment).y1 - (segment).y0)

extern s32 sub_0802BF34(s32 x0, s32 y0, s32 x1, s32 y1);
extern u8 sub_0802C018(s32 x, s32 y, u32 fourWay);

// Turns an object around: its facing becomes the opposite one and its velocity is negated.
inline void ReverseObjectDirection(Object *obj)
{
    u32 facing = obj->bFacing;

    if (obj->dwFlags & ObjectFlagFourWayDirections_candidate)
        facing = g_abOppositeFacing[facing * 2] / 2;
    else
        facing = g_abOppositeFacing[facing];
    obj->bFacing = facing;
    obj->nVelX = -obj->nVelX;
    obj->nVelY = -obj->nVelY;
}

// Sets the velocity that takes the object from its previous position to its move target at
// speed dwUnk_0x28 and returns the direction of the velocity it replaced. Nothing calls it.
inline u8 StartMoveVelocity(Object *obj)
{
    s32 distance;
    s32 steps;
    s32 dx;
    s32 dy;
    u8 direction;

    distance = sub_0802BF34(obj->nMoveTargetX, obj->nMoveTargetY, obj->nXPrev, obj->nYPrev);
    steps = ABS(iwramDivideSignedQuotient(distance, obj->dwUnk_0x28));
    dx = obj->nMoveTargetX - obj->nXPrev;
    dy = obj->nMoveTargetY - obj->nYPrev;
    direction = sub_0802C018(obj->nVelX, obj->nVelY, obj->dwFlags & ObjectFlagFourWayDirections_candidate);
    obj->nVelX = iwramDivideSignedQuotient(dx, steps);
    obj->nVelY = iwramDivideSignedQuotient(dy, steps);
    return direction;
}

// Fills box with the pixel edges of the object's terrain box around its previous position.
inline void GetObjectTerrainBox(Object *obj, TerrainBox *box)
{
    s32 y = (s16)(obj->nYPrev >> 16);
    s32 x = (s16)(obj->nXPrev >> 16);

    box->top = y + obj->bTerrainBoxTop;
    box->bottom = y + obj->bTerrainBoxBottom;
    box->left = x + obj->bTerrainBoxLeft;
    box->right = x + obj->bTerrainBoxRight;
}

// Collision types 1-25 (solid and slope terrain) block movement.
inline u32 IsBlockingCollisionType(u32 type)
{
    return type >= 1 && type <= 25;
}

// Returns the collision type at a room pixel: the low 6 bits of its behavior byte, 1 outside the
// room, and for the slope types 2-25 either 0 or the type depending on which side of the
// slope's line the pixel is on.
u32 GetCollisionTypeAtPixel_candidate(PixelPoint pixel)
{
    SlopeLineSegment segment;
    PixelVector line;
    PixelVector offset;
    u32 block;
    u32 cell;
    u32 type;

    if (pixel.x > g_RoomSizePixels.dwWidth || pixel.y > g_RoomSizePixels.dwHeight)
        return 1;

    block = COLLISION_BLOCK_PATTERN_ID(
        g_pRoomCollisionTilemap[(pixel.x >> 5) + (pixel.y >> 5) * (g_RoomSizePixels.dwWidth >> 5)]);
    cell = ((pixel.x >> 3) & 3) | ((pixel.y >> 1) & 0xC);
    type = g_pRoomCollisionBehaviorTable[block * 16 | cell] & 0x3F;

    if (type >= 2 && type <= 25)
    {
        segment = g_aSlopeLineSegments[type - 2];
        line.x = SEGMENT_DX(segment);
        line.y = SEGMENT_DY(segment);
        offset.x = (pixel.x & 7) - segment.x0;
        offset.y = (pixel.y & 7) - segment.y0;
        if (line.x * offset.y - offset.x * line.y < 0)
            return 0;
    }

    return type;
}

// Fills box with the object's terrain box edges and returns the collision type it runs into
// while facing in its current direction (a diagonal facing tries its first edge, then the
// second), after applying the terrain's side effects.
u32 GetObjectTerrainType(Object *obj, TerrainBox *box)
{
    u8 facing;
    u32 type;

    GetObjectTerrainBox(obj, box);

    facing = obj->bFacing;
    if (facing & 1)
    {
        type = ScanTerrainEdge(facing & 0xFE, box);
        if (!IsBlockingCollisionType(type))
            type = ScanTerrainEdge((facing + 1) & 7, box);
    }
    else
        type = ScanTerrainEdge(facing, box);

    type = ApplyTerrainTypeEffect(obj, box, type);
    return type;
}

// Applies the side effects of the terrain type an object touched and returns the type to
// treat it as: types the object may not enter become 1.
u32 ApplyTerrainTypeEffect(Object *obj, TerrainBox *box, u32 type)
{
    obj->dwFlags &= ~ObjectFlagAnimPaused;

    switch (type)
    {
    case 0x22:
        if (obj->wObjectType == 0)
            type = 1;
        else if (obj->wObjectType == 5)
        {
            if (GetCollisionTypeAtPixel_candidate((PixelPoint){ box->left, box->top }) != 0x22)
                break;
            if (GetCollisionTypeAtPixel_candidate((PixelPoint){ box->right, box->top }) != 0x22)
                break;
            if (GetCollisionTypeAtPixel_candidate((PixelPoint){ box->left, box->bottom }) != 0x22)
                break;
            if (GetCollisionTypeAtPixel_candidate((PixelPoint){ box->right, box->bottom }) != 0x22)
                break;
            if (obj->bActionSubState == 1 && !(obj->dwFlags & ObjectFlagNoPushTrigger_candidate))
                sub_08046C5C(obj);
        }
        break;
    case 0x1F:
        if (g_dwPendingCameraFocusFlag == 0 || g_pPlayerObject->bFighterIndex != 1)
            type = 1;
        break;
    case 0x29:
        if (obj->wObjectType != 0xF)
            type = 1;
        break;
    case 0x23:
        if (SetRoomSwitchState(0))
            ApplyRoomSwitchEffect(0);
        break;
    case 0x24:
        if (SetRoomSwitchState(1))
            ApplyRoomSwitchEffect(1);
        break;
    case 0x2D:
        if (obj == g_pPlayerObject)
            obj->dwFlags |= ObjectFlagAnimPaused;
        break;
    }

    return type;
}

// Reacts to the terrain an object has run into according to bUnk_0x7C: undoes the move,
// reverses the object's direction, or ends an ice slide. Always records the terrain type under
// the object.
void RespondToTerrain(Object *obj, u32 type)
{
    if (IsBlockingCollisionType(type))
    {
        switch (obj->bUnk_0x7C)
        {
        case 5:
            obj->nXPrev = obj->nX;
            obj->nYPrev = obj->nY;
            if (!TrySlideAlongSlope(obj, type))
            {
                if ((u8)(obj->bActionState - 7) > 6)
                {
                    SetObjectActionSubState(obj, 2);
                    CancelObjectMove_candidate(obj);
                    if (obj == g_pPlayerObject)
                        sub_08024518(obj, 0);
                }
            }
            break;
        case 1:
            obj->nXPrev = obj->nX;
            obj->nYPrev = obj->nY;
            SetObjectActionSubState(obj, 2);
            break;
        case 4:
            obj->nXPrev = obj->nX;
            obj->nYPrev = obj->nY;
            SetObjectActionSubState(obj, 5);
            break;
        case 2:
            ReverseObjectDirection(obj);
            break;
        case 3:
            break;
        }
    }

    obj->bTerrainType = GetCollisionTypeAtPixel_candidate(
        (PixelPoint){ (s16)(obj->nXPrev >> 16), (s16)(obj->nYPrev >> 16) });
}

// Moves an object that is blocked by a slope along it, trying the slope's own direction and
// then the edges of its tile. Returns nonzero if a nudge was accepted.
u32 TrySlideAlongSlope(Object *obj, u32 type)
{
    PixelVector delta;
    u32 edge = obj->bFacing >> 1;

    if (type != 1)
    {
        type -= 2;
        delta.x = SEGMENT_DX(g_aSlopeLineSegments[type]);
        delta.y = SEGMENT_DY(g_aSlopeLineSegments[type]);
        if (!NudgeAlongVelocity(obj, delta))
            return 1;
    }

    if (obj->bFacing & 1)
    {
        delta.x = SEGMENT_DX(g_aTileEdgeSegments[edge]);
        delta.y = SEGMENT_DY(g_aTileEdgeSegments[edge]);
        if (!NudgeAlongVelocity(obj, delta))
            return 1;
        edge = (edge + 1) & 3;
    }

    delta.x = SEGMENT_DX(g_aTileEdgeSegments[edge]);
    delta.y = SEGMENT_DY(g_aTileEdgeSegments[edge]);
    if (!NudgeAlongVelocity(obj, delta))
        return 1;

    delta.x = SEGMENT_DX(g_aTileEdgeSegments[edge]) << 14;
    delta.y = SEGMENT_DY(g_aTileEdgeSegments[edge]) << 14;
    if (g_adwEdgeEndpointTypes[0] == 0)
    {
        if (g_adwEdgeEndpointTypes[1] == 0)
        {
            if (!TryNudgeObject(obj, delta))
                return 1;
            delta.x = -delta.x;
            delta.y = -delta.y;
        }
    }
    else
    {
        if (g_adwEdgeEndpointTypes[1] != 0)
            return 0;
        delta.x = -delta.x;
        delta.y = -delta.y;
    }

    return !TryNudgeObject(obj, delta);
}

// Samples the terrain along one edge of the box in 4-pixel steps (direction 0 = top edge left to
// right, 2 = right edge top to bottom, 4 = bottom edge right to left, 6 = left edge bottom to top)
// and returns the type of the first blocking tile, else the last nonzero type found, else the
// type at the edge's end. The first scan for an object also stores its two end types in
// g_adwEdgeEndpointTypes. direction is always even; other values leave the probe unset.
u32 ScanTerrainEdge(u32 direction, TerrainBox *box)
{
    PixelPoint pos;
    PixelPoint end;
    PixelVector step;
    s32 length;
    s32 i;
    u32 result = 0;
    u32 type;

    switch (direction)
    {
    case 0:
        pos.x = box->left;
        pos.y = box->top;
        end.x = box->right;
        end.y = box->top;
        step.x = 1;
        step.y = 0;
        length = box->right - box->left;
        break;
    case 2:
        pos.x = box->right;
        pos.y = box->top;
        end.x = box->right;
        end.y = box->bottom;
        step.x = 0;
        step.y = 1;
        length = box->bottom - box->top;
        break;
    case 4:
        pos.x = box->right;
        pos.y = box->bottom;
        end.x = box->left;
        end.y = box->bottom;
        step.x = -1;
        step.y = 0;
        length = box->right - box->left;
        break;
    case 6:
        pos.x = box->left;
        pos.y = box->bottom;
        end.x = box->left;
        end.y = box->top;
        step.x = 0;
        step.y = -1;
        length = box->bottom - box->top;
        break;
    default:
        length = 0;
        break;
    }

    if (g_adwEdgeEndpointTypes[0] == 0xFF)
    {
        g_adwEdgeEndpointTypes[0] = GetCollisionTypeAtPixel_candidate(end);
        g_adwEdgeEndpointTypes[1] = GetCollisionTypeAtPixel_candidate(pos);
    }

    for (i = 0; i < length; i += 4)
    {
        type = GetCollisionTypeAtPixel_candidate(pos);
        if (type != 0)
        {
            result = type;
            if (IsBlockingCollisionType(type))
                break;
        }
        pos.x += step.x * 4;
        pos.y += step.y * 4;
    }

    if (!IsBlockingCollisionType(result))
    {
        type = GetCollisionTypeAtPixel_candidate(end);
        if (type != 0)
            result = type;
    }

    return result;
}

// Empty subsystem initializer; AgbMain calls it once at startup.
void NoopInit2(void)
{
}

// Loads the room's collision behavior table and collision tilemap; see
// docs/formats/collision.md.
void LoadRoomSharedTileset_candidate(const void *pCollisionBehaviorTable, const void *pCollisionTilemap)
{
    u32 size;

    size = GetResourceDecompressedSize(pCollisionBehaviorTable);
    g_pRoomCollisionBehaviorTable = AllocBlock(size);
    DecompressResource(pCollisionBehaviorTable, g_pRoomCollisionBehaviorTable);

    size = GetResourceDecompressedSize(pCollisionTilemap);
    g_pRoomCollisionTilemapBuffer = AllocBlock(size);
    g_pRoomCollisionTilemap = (u16 *)(g_pRoomCollisionTilemapBuffer + 4);
    DecompressResource(pCollisionTilemap, g_pRoomCollisionTilemapBuffer);
    g_dwRoomCollisionPatternCount = *(u16 *)g_pRoomCollisionTilemapBuffer;
}

// Frees the room's collision data.
void FreeRoomSharedTileset(void)
{
    FreeBlock(g_pRoomCollisionBehaviorTable);
    FreeBlock(g_pRoomCollisionTilemapBuffer);
    g_pRoomCollisionTilemap = NULL;
}

// Sets the collision pattern id of the 32x32-pixel block containing a room pixel.
void SetRoomCollisionPattern(u16 x, u16 y, u16 patternId)
{
    u16 *pPattern = &g_pRoomCollisionTilemap[(x >> 5) + (y >> 5) * (g_RoomSizePixels.dwWidth >> 5)];

    *pPattern = patternId;
}

// Returns the collision pattern id of the 32x32-pixel block containing a room pixel.
u16 GetRoomCollisionPattern(u16 x, u16 y)
{
    u16 *pPattern = &g_pRoomCollisionTilemap[(x >> 5) + (y >> 5) * (g_RoomSizePixels.dwWidth >> 5)];

    return *pPattern;
}
