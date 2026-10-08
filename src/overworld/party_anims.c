#include "types.h"
#include "graphics/object.h"
#include "graphics/object_anim.h"
#include "gen/graphics/overworld.h"
#include "overworld/overworld.h"

// Indexed by Object.bFacing; see SetPartyMemberAnim. Facings 5-7 mirror 3-1 with
// oam.hFlip set.

const u8 g_abPartyStandFrames[8] = { 4, 3, 2, 1, 0, 1, 2, 3 };

const u8 g_abPartyStandFramesChar8[8] = { 2, 1, 1, 1, 0, 1, 1, 1 };

const u8 g_aPartyWalkAnims[8][18] = {
    {
        ANIM_FRAME(37, 3), ANIM_FRAME(38, 3), ANIM_FRAME(39, 3), ANIM_FRAME(40, 3),
        ANIM_FRAME(41, 3), ANIM_FRAME(42, 3), ANIM_FRAME(43, 3), ANIM_FRAME(44, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(29, 3), ANIM_FRAME(30, 3), ANIM_FRAME(31, 3), ANIM_FRAME(32, 3),
        ANIM_FRAME(33, 3), ANIM_FRAME(34, 3), ANIM_FRAME(35, 3), ANIM_FRAME(36, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3),
        ANIM_FRAME(25, 3), ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_FRAME(28, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3),
        ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3),
        ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3),
        ANIM_FRAME(25, 3), ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_FRAME(28, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(29, 3), ANIM_FRAME(30, 3), ANIM_FRAME(31, 3), ANIM_FRAME(32, 3),
        ANIM_FRAME(33, 3), ANIM_FRAME(34, 3), ANIM_FRAME(35, 3), ANIM_FRAME(36, 3),
        ANIM_JUMP(0),
    },
};

const u8 g_aPartyWalkAnimsChar8[8][14] = {
    {
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
};

const u8 g_aPartyWalkAnimsChar4[8][18] = {
    {
        ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_FRAME(22, 2),
        ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_FRAME(22, 2),
        ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2),
        ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2),
        ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2),
        ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2),
        ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2),
        ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2), ANIM_FRAME(18, 2),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2), ANIM_FRAME(22, 2),
        ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2),
        ANIM_JUMP(0),
    },
};

const u8 g_aPartyCastAnims[8][18] = {
    {
        ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2), ANIM_FRAME(27, 6),
        ANIM_FRAME(28, 2), ANIM_FRAME(29, 5), ANIM_EVENT(0), ANIM_FRAME(29, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 6),
        ANIM_FRAME(22, 2), ANIM_FRAME(23, 5), ANIM_EVENT(0), ANIM_FRAME(23, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 6),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 5), ANIM_EVENT(0), ANIM_FRAME(17, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 6),
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_EVENT(0), ANIM_FRAME(11, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 6),
        ANIM_FRAME(4, 2), ANIM_FRAME(5, 5), ANIM_EVENT(0), ANIM_FRAME(5, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 6),
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_EVENT(0), ANIM_FRAME(11, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 2), ANIM_FRAME(15, 6),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 5), ANIM_EVENT(0), ANIM_FRAME(17, 5),
        ANIM_END,
    },
    {
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 6),
        ANIM_FRAME(22, 2), ANIM_FRAME(23, 5), ANIM_EVENT(0), ANIM_FRAME(23, 5),
        ANIM_END,
    },
};

const u8 g_aPartyAnim4Anims[8][4] = {
    { ANIM_FRAME(2, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(0, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(1, 3), ANIM_END },
};

const u8 g_abPartyAnim3Anim[22] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
    ANIM_EVENT(0), ANIM_FRAME(7, 10), ANIM_END,
};

const ObjectGfxRecord g_UnusedPartyGfx2 = {
    (void *)gOverworldPlayer019Tiles, (void *)gOverworldPlayer019Frames,
};
