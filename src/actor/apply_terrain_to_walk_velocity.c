#include "types.h"
#include "math.h"
#include "actor.h"
#include "overworld/overworld.h"

// Sets the walk velocity (nMoveSpeed in `direction`) and returns the facing to show.
// On stairs (collision types 0x1B-0x28, see docs/formats/collision.md) the velocity
// follows the stairs' slope; on ice (0x2D) the velocity is kept and so is the facing.
s8 ApplyTerrainToWalkVelocity(Actor *actor, s8 direction)
{
    switch (actor->bTerrainType) {
    case 0x2D:
        if ((actor->vel.x != 0 || actor->vel.y != 0) && direction != actor->bFacing)
            direction = actor->bFacing;
        break;
    case 0x1B:
        if (actor->vel.x > 0 || (actor->vel.x >= 0 && actor->vel.y < 0)) {
            actor->vel.x = 0x10000;
            actor->vel.y = -0x8000;
            direction = DirectionRight;
        }
        else if (actor->vel.x < 0 || actor->vel.y > 0) {
            actor->vel.x = -0x10000;
            actor->vel.y = 0x8000;
            direction = DirectionLeft;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    case 0x1C:
        if (actor->vel.x > 0 || (actor->vel.x >= 0 && actor->vel.y > 0)) {
            actor->vel.x = 0x10000;
            actor->vel.y = 0x8000;
            direction = DirectionRight;
        }
        else if (actor->vel.x < 0 || actor->vel.y < 0) {
            actor->vel.x = -0x10000;
            actor->vel.y = -0x8000;
            direction = DirectionLeft;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    case 0x25:
        if (actor->vel.x > 0 || (actor->vel.x >= 0 && actor->vel.y < 0)) {
            actor->vel.x = 0xB505;
            actor->vel.y = -0xD4DB;
            direction = DirectionUpRight;
        }
        else if (actor->vel.x < 0 || actor->vel.y > 0) {
            actor->vel.x = -0xB505;
            actor->vel.y = 0xD4DB;
            direction = DirectionDownLeft;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    case 0x28:
        if (actor->vel.x > 0) {
            actor->vel.x = 0xB505;
            actor->vel.y = 0xD4DB;
            direction = DirectionDownRight;
        }
        else if (actor->vel.x < 0) {
            actor->vel.x = -0xB505;
            actor->vel.y = -0xD4DB;
            direction = DirectionUpLeft;
        }
        else if (actor->vel.y < 0) {
            actor->vel.x = -0xB505;
            actor->vel.y = -0xD4DB;
            direction = DirectionUpLeft;
        }
        else if (actor->vel.y > 0) {
            actor->vel.x = 0xB505;
            actor->vel.y = 0xD4DB;
            direction = DirectionDownRight;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    case 0x26:
        SetPlayerShadowVisible(0);
        if (actor->vel.x > 0 || (actor->vel.x >= 0 && actor->vel.y < 0)) {
            actor->vel.x = 0xEC83;
            actor->vel.y = -0x49F4;
            direction = DirectionDownRight;
        }
        else if (actor->vel.x < 0 || actor->vel.y > 0) {
            actor->vel.x = -0xEC83;
            actor->vel.y = 0x49F4;
            direction = DirectionUpLeft;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    case 0x27:
        SetPlayerShadowVisible(0);
        if (actor->vel.x > 0) {
            actor->vel.x = 0xEC83;
            actor->vel.y = 0x49F4;
            direction = DirectionUpRight;
        }
        else if (actor->vel.x < 0) {
            actor->vel.x = -0xEC83;
            actor->vel.y = -0x49F4;
            direction = DirectionDownLeft;
        }
        else if (actor->vel.y < 0) {
            actor->vel.x = -0xEC83;
            actor->vel.y = -0x49F4;
            direction = DirectionDownLeft;
        }
        else if (actor->vel.y > 0) {
            actor->vel.x = 0xEC83;
            actor->vel.y = 0x49F4;
            direction = DirectionUpRight;
        }
        else {
            actor->vel.x = 0;
            actor->vel.y = 0;
        }
        actor->vel.x = FixedMultiply(actor->vel.x, actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(actor->vel.y, actor->nMoveSpeed);
        break;
    default:
        SetPlayerShadowVisible(1);
        actor->vel.x = FixedMultiply(g_aDirection8Vectors[direction][0], actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(g_aDirection8Vectors[direction][1], actor->nMoveSpeed);
        break;
    }

    return direction;
}
