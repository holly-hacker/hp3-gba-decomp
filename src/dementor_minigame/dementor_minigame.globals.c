#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "math.h"
#include "dementor_minigame.h"

const DementorMinigameSprite g_DementorMinigameDementorSprite = {
    { (void *)gDementorTiles, (void *)gDementorFrames, (void *)gDementorPalette, 0 },
    (const ObjPalette *)gDementorPalette,
};

const DementorMinigameSprite g_DementorMinigameHarrySprite = {
    { (void *)gHarryWalkTiles, (void *)gHarryWalkFrames, (void *)gHarryWalkPalette, 0 },
    (const ObjPalette *)gHarryWalkPalette,
};

const DementorMinigameSprite g_DementorMinigameHarryCastSprite = {
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames,
      (void *)gOverworldPlayer001Palette, 0 },
    (const ObjPalette *)gOverworldPlayer001Palette,
};

const DementorMinigameSprite g_DementorMinigameSpellSprite = {
    { (void *)gDementorMinigameSpellTiles, (void *)gDementorMinigameSpellFrames,
      (void *)gDementorMinigameSpellPalette, 0 },
    (const ObjPalette *)gDementorMinigameSpellPalette,
};

const DementorMinigameSprite g_DementorMinigameDamageSprite = {
    { (void *)gDementorMinigameDamageTiles, (void *)gDementorMinigameDamageFrames,
      (void *)gDementorMinigameDamagePalette, 0 },
    (const ObjPalette *)gDementorMinigameDamagePalette,
};

const u32 g_dwDementorMinigameBg0Control = 0x3F03;
const u32 g_dwDementorMinigameBg3Control = 0x3E08;

// Dementor start positions by direction; Harry stands at (0x78, 0x78).
const IntPoint g_aDementorStartPositions[4] = {
    { 0xB8, 0x78 },
    { 0x78, 0xB8 },
    { 0x38, 0x78 },
    { 0x78, 0x38 },
};

// Holds the first frame of each fly cycle. Not referenced by the minigame code.
const u8 g_aabDementorStopAnimData[4][2] = {
    { ANIM_FRAME(8, 0) },
    { ANIM_FRAME(16, 0) },
    { ANIM_FRAME(8, 0) },
    { ANIM_FRAME(0, 0) },
};

const u8 g_aabDementorFlyAnimData[4][18] = {
    {
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_FRAME(22, 2), ANIM_FRAME(23, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_JUMP(0),
    },
};

// Plays the cast and returns to the standing frame.
const u8 g_aabDementorMinigameHarryCastAnimData[4][14] = {
    {
        ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1),
        ANIM_FRAME(16, 1), ANIM_FRAME(17, 10), ANIM_FRAME(12, 0),
    },
    {
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 10), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1),
        ANIM_FRAME(16, 1), ANIM_FRAME(17, 10), ANIM_FRAME(12, 0),
    },
    {
        ANIM_FRAME(24, 1), ANIM_FRAME(25, 1), ANIM_FRAME(26, 1), ANIM_FRAME(27, 1),
        ANIM_FRAME(28, 1), ANIM_FRAME(29, 10), ANIM_FRAME(24, 0),
    },
};

const u8 g_aabDementorMinigameSpellAnimData[4][6] = {
    { ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_JUMP(0) },
    { ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_JUMP(0) },
    { ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_JUMP(0) },
    { ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_JUMP(0) },
};

const IntPoint g_aDementorMinigameSpellPositions[4] = {
    { 0x8D, 0x61 },
    { 0x77, 0x76 },
    { 0x62, 0x61 },
    { 0x7C, 0x54 },
};

// Plays frames 0-16 and holds the last.
const u8 g_abDementorMinigameDamageAnimData[34] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
    ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1), ANIM_FRAME(11, 1),
    ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1),
    ANIM_FRAME(16, 0),
};
