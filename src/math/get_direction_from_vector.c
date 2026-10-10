#include "math.h"
#include "graphics/object.h"

// Index bits: 1 = x negative, 2 = y negative, 4 = mostly horizontal,
// 8 = mostly vertical (eight-way only). Neither 4 nor 8 is a diagonal.
u8 GetDirectionFromVector(FixedPoint v, u32 fourWay)
{
    u8 index = 0;
    u8 directions8[16] = {
        DirectionDownRight, DirectionDownLeft, DirectionUpRight, DirectionUpLeft,
        DirectionRight, DirectionLeft, DirectionRight, DirectionLeft,
        DirectionDown, DirectionDown, DirectionUp, DirectionUp,
        DirectionDownRight, DirectionDownLeft, DirectionUpRight, DirectionUpLeft,
    };
    u8 directions4[8] = {
        Direction4Down, Direction4Down, Direction4Up, Direction4Up,
        Direction4Right, Direction4Left, Direction4Right, Direction4Left,
    };

    if (v.x < 0)
    {
        v.x = -v.x;
        index = 1;
    }
    if (v.y < 0)
    {
        v.y = -v.y;
        index |= 2;
    }

    if (fourWay)
    {
        if (v.x > v.y)
            index |= 4;
        return directions4[index];
    }

    if (v.x > v.y * 2)
        index |= 4;
    if (v.x * 2 < v.y)
        index |= 8;
    return directions8[index];
}
