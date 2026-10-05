#include "types.h"
#include "graphics/graphics.h"

// Unit vectors in 16.16 fixed point, indexed by Direction4 and Direction.
// Diagonals are scaled by 0xB504 (1/sqrt(2)); screen y grows downward.
const s32 g_aDirection4Vectors[4][2] = {
    {        0, -0x10000 },  // Up
    {  0x10000,        0 },  // Right
    {        0,  0x10000 },  // Down
    { -0x10000,        0 },  // Left
};

const s32 g_aDirection8Vectors[8][2] = {
    {       0, -0x10000 },  // Up
    {  0xB504,  -0xB504 },  // UpRight
    { 0x10000,        0 },  // Right
    {  0xB504,   0xB504 },  // DownRight
    {       0,  0x10000 },  // Down
    { -0xB504,   0xB504 },  // DownLeft
    { -0x10000,       0 },  // Left
    { -0xB504,  -0xB504 },  // UpLeft
};
