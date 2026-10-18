#include "types.h"
#include "actor.h"

// Unit vectors in 16.16 fixed point, indexed by Direction4 and Direction, then
// 16 and 32 evenly spaced directions clockwise from up.
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

const s32 g_aDirection16Vectors[16][2] = {
    {        0, -0x10000 },
    {   0x61F7,  -0xEC83 },
    {   0xB504,  -0xB504 },
    {   0xEC83,  -0x61F7 },
    {  0x10000,        0 },
    {   0xEC83,   0x61F7 },
    {   0xB504,   0xB504 },
    {   0x61F7,   0xEC83 },
    {        0,  0x10000 },
    {  -0x61F7,   0xEC83 },
    {  -0xB504,   0xB504 },
    {  -0xEC83,   0x61F7 },
    { -0x10000,        0 },
    {  -0xEC83,  -0x61F7 },
    {  -0xB504,  -0xB504 },
    {  -0x61F7,  -0xEC83 },
};

const s32 g_aDirection32Vectors[32][2] = {
    {        0, -0x10000 },
    {   0x31F1,  -0xFB14 },
    {   0x61F7,  -0xEC83 },
    {   0x8E39,  -0xD4DB },
    {   0xB504,  -0xB504 },
    {   0xD4DB,  -0x8E39 },
    {   0xEC83,  -0x61F7 },
    {   0xFB14,  -0x31F1 },
    {  0x10000,        0 },
    {   0xFB14,   0x31F1 },
    {   0xEC83,   0x61F7 },
    {   0xD4DB,   0x8E39 },
    {   0xB504,   0xB504 },
    {   0x8E39,   0xD4DB },
    {   0x61F7,   0xEC83 },
    {   0x31F1,   0xFB14 },
    {        0,  0x10000 },
    {  -0x31F1,   0xFB14 },
    {  -0x61F7,   0xEC83 },
    {  -0x8E39,   0xD4DB },
    {  -0xB504,   0xB504 },
    {  -0xD4DB,   0x8E39 },
    {  -0xEC83,   0x61F7 },
    {  -0xFB14,   0x31F1 },
    { -0x10000,        0 },
    {  -0xFB14,  -0x31F1 },
    {  -0xEC83,  -0x61F7 },
    {  -0xD4DB,  -0x8E39 },
    {  -0xB504,  -0xB504 },
    {  -0x8E39,  -0xD4DB },
    {  -0x61F7,  -0xEC83 },
    {  -0x31F1,  -0xFB14 },
};

// Direction reflected vertically ((N/2 - d) mod N); Right and Left reverse instead.
// Not referenced by any code.
const u8 g_abDirection16FlipY[16] = { 8, 7, 6, 5, 12, 3, 2, 1, 0, 15, 14, 13, 4, 11, 10, 9 };

const u8 g_abDirection32FlipY[32] = {
    16, 15, 14, 13, 12, 11, 10, 9, 24, 7, 6, 5, 4, 3, 2, 1,
    0, 31, 30, 29, 28, 27, 26, 25, 8, 23, 22, 21, 20, 19, 18, 17,
};
