#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "math.h"
#include "boggart_minigame.h"
#include "gen/graphics/minigames/boggart.h"

const ActorAssetRecord g_aBoggartStudentAssets[4] = {
    { (void *)gBoggartStudent0Tiles, (void *)gBoggartStudent0Frames, (void *)gBoggartStudent0Palette, 0 },
    { (void *)gBoggartStudent1Tiles, (void *)gBoggartStudent1Frames, (void *)gBoggartStudent1Palette, 0 },
    { (void *)gBoggartStudent2Tiles, (void *)gBoggartStudent2Frames, (void *)gBoggartStudent2Palette, 0 },
    { (void *)gBoggartStudent3Tiles, (void *)gBoggartStudent3Frames, (void *)gBoggartStudent3Palette, 0 },
};

const ObjPalette *const g_apBoggartStudentPalettes[4] = {
    (const ObjPalette *)gBoggartStudent0Palette,
    (const ObjPalette *)gBoggartStudent1Palette,
    (const ObjPalette *)gBoggartStudent2Palette,
    (const ObjPalette *)gBoggartStudent3Palette,
};

const ActorAssetRecord g_aBoggartCastEffectAssets[4] = {
    { (void *)gBoggartCastEffect0Tiles, (void *)gBoggartCastEffect0Frames, (void *)gBoggartCastEffect0Palette, 0 },
    { (void *)gBoggartCastEffect1Tiles, (void *)gBoggartCastEffect1Frames, (void *)gBoggartCastEffect1Palette, 0 },
    { (void *)gBoggartCastEffect2Tiles, (void *)gBoggartCastEffect2Frames, (void *)gBoggartCastEffect2Palette, 0 },
    { (void *)gBoggartCastEffect3Tiles, (void *)gBoggartCastEffect3Frames, (void *)gBoggartCastEffect3Palette, 0 },
};

const ObjPalette *const g_apBoggartCastEffectPalettes[4] = {
    (const ObjPalette *)gBoggartCastEffect0Palette,
    (const ObjPalette *)gBoggartCastEffect1Palette,
    (const ObjPalette *)gBoggartCastEffect2Palette,
    (const ObjPalette *)gBoggartCastEffect3Palette,
};

// Entry 4 is the form the Boggart takes once the charm lands.
const ActorAssetRecord g_aBoggartFormAssets[5] = {
    { (void *)gBoggartForm0Tiles, (void *)gBoggartForm0Frames, (void *)gBoggartForm0Palette, 0 },
    { (void *)gBoggartForm1Tiles, (void *)gBoggartForm1Frames, (void *)gBoggartForm1Palette, 0 },
    { (void *)gBoggartForm2Tiles, (void *)gBoggartForm2Frames, (void *)gBoggartForm2Palette, 0 },
    { (void *)gBoggartForm3Tiles, (void *)gBoggartForm3Frames, (void *)gBoggartForm3Palette, 0 },
    { (void *)gBoggartRidiculousFormTiles, (void *)gBoggartRidiculousFormFrames,
      (void *)gBoggartRidiculousFormPalette, 0 },
};

const ObjPalette *const g_apBoggartFormPalettes[5] = {
    (const ObjPalette *)gBoggartForm0Palette,
    (const ObjPalette *)gBoggartForm1Palette,
    (const ObjPalette *)gBoggartForm2Palette,
    (const ObjPalette *)gBoggartForm3Palette,
    (const ObjPalette *)gBoggartRidiculousFormPalette,
};

const u32 g_dwBoggartMinigameBg0Control = 0x3F03;
const u32 g_dwBoggartMinigameBg3Control = 0x3E08;

// Student positions by direction; the Boggart spawns at (0x78, 0x65).
const IntPoint g_aBoggartStudentPositions[4] = {
    { 0xB8, 0x65 },
    { 0x78, 0xA5 },
    { 0x38, 0x65 },
    { 0x78, 0x25 },
};

// Plays frames 0-6 and holds the last.
const u8 g_abBoggartStudentCastAnimData[14] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 0),
};

const u8 g_abBoggartCastEffectAnimData[12] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_JUMP(0),
};

const u8 g_abBoggartStopAnimData[2] = {
    ANIM_FRAME(0, 0),
};

// Walk cycles by direction, one 30-byte slot each.
const u8 g_aabBoggartWalkAnimData[4][30] = {
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
        ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2), ANIM_FRAME(11, 2),
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_JUMP(0),
    },
};

// Played on the Boggart's final form once the charm lands, by direction.
const u8 g_aabBoggartHitAnimData[4][6] = {
    { ANIM_FRAME(0, 5), ANIM_JUMP(0) },
    { ANIM_FRAME(6, 5), ANIM_FRAME(7, 5), ANIM_JUMP(0) },
    { ANIM_FRAME(6, 5), ANIM_FRAME(7, 5), ANIM_JUMP(0) },
    { ANIM_FRAME(14, 5), ANIM_FRAME(15, 5), ANIM_JUMP(0) },
};
