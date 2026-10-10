#pragma once

// Eight-way direction, clockwise from up (screen y grows downward). Odd
// values are diagonals. DirectionNone: no direction, as when within tolerance
// of a target on both axes or with no single D-pad direction held.
typedef enum {
    DirectionUp,
    DirectionUpRight,
    DirectionRight,
    DirectionDownRight,
    DirectionDown,
    DirectionDownLeft,
    DirectionLeft,
    DirectionUpLeft,
    DirectionNone,
} Direction;

// Four-way direction returned for ObjectFlagFourWayDirections_candidate.
typedef enum {
    Direction4Up,
    Direction4Right,
    Direction4Down,
    Direction4Left,
    Direction4None,
} Direction4;
