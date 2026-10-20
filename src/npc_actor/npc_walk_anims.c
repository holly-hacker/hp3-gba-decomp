#include "types.h"
#include "actor_anim.h"
#include "npc_actor.h"

// An NPC's walk animation for each Direction4 facing, in the same rows as
// g_abRoomActorUnk6Frames (selected by g_adwRoomActorUnk6FrameRows).
const u8 g_aaabNpcWalkAnims[12][4][30] = {
    {  // 0
        {
            ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3),
            ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3),
            ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3),
            ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_JUMP(0),
        },
    },
    {  // 1
        {
            ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
            ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_JUMP(0),
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
    },
    {  // 2
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
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3),
            ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3),
            ANIM_JUMP(0),
        },
    },
    {  // 3
        {
            ANIM_FRAME(37, 3), ANIM_FRAME(38, 3), ANIM_FRAME(39, 3), ANIM_FRAME(40, 3),
            ANIM_FRAME(41, 3), ANIM_FRAME(42, 3), ANIM_FRAME(43, 3), ANIM_FRAME(44, 3),
            ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3),
            ANIM_FRAME(25, 3), ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_FRAME(28, 3),
            ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3),
            ANIM_FRAME(25, 3), ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_FRAME(28, 3),
            ANIM_JUMP(0),
        },
    },
    {  // 4
        { 0 },
        { 0 },
        { 0 },
        { 0 },
    },
    {  // 5
        {
            ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3), ANIM_FRAME(19, 3),
            ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3),
            ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
            ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
            ANIM_JUMP(0),
        },
    },
    {  // 6
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
            ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_JUMP(0),
        },
    },
    {  // 7
        {
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_JUMP(0),
        },
    },
    {  // 8
        {
            ANIM_FRAME(0, 1), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 1),
            ANIM_FRAME(8, 2), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 1), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 1),
            ANIM_FRAME(8, 2), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 1), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 1),
            ANIM_FRAME(8, 2), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 1), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 1),
            ANIM_FRAME(8, 2), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_JUMP(0),
        },
    },
    {  // 9
        {
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        },
    },
    {  // 10
        {
            ANIM_FRAME(4, 0),
        },
        {
            ANIM_FRAME(2, 0),
        },
        { 0 },
        {
            ANIM_FRAME(2, 0),
        },
    },
    {  // 11
        {
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_JUMP(0),
        },
        {
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_JUMP(0),
        },
    },
};
