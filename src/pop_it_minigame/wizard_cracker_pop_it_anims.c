#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "pop_it_minigame.h"
#include "gen/graphics/battle.h"
#include "gen/graphics/minigames/wizard_cracker.h"

const ActorAssetRecord g_aWizardCrackerPopItPopAssets[WIZARD_CRACKER_POP_IT_KINDS] = {
    { NULL, NULL, NULL, 1 },  // The wrapped cracker pops within its own sprite.
    { (void *)gWizardCrackerTrianglePopTiles, (void *)gWizardCrackerTrianglePopFrames, NULL, 1 },
    { (void *)gWizardCrackerOvalPopTiles, (void *)gWizardCrackerOvalPopFrames, NULL, 1 },
    { (void *)gWizardCrackerDumbbellPopTiles, (void *)gWizardCrackerDumbbellPopFrames, NULL, 1 },
    // The sweet cracker's pop is shared with a battle effect.
    { (void *)gBattleEffect2_001Tiles, (void *)gBattleEffect2_001Frames, NULL, 1 },
};

const ActorAssetRecord g_aWizardCrackerPopItCrackerAssets[WIZARD_CRACKER_POP_IT_KINDS] = {
    { (void *)gWizardCrackerWrappedSpriteTiles, (void *)gWizardCrackerWrappedSpriteFrames, NULL, 1 },
    { (void *)gWizardCrackerTriangleSpriteTiles, (void *)gWizardCrackerTriangleSpriteFrames, NULL, 1 },
    { (void *)gWizardCrackerOvalSpriteTiles, (void *)gWizardCrackerOvalSpriteFrames, NULL, 1 },
    { (void *)gWizardCrackerDumbbellSpriteTiles, (void *)gWizardCrackerDumbbellSpriteFrames, NULL, 1 },
    { (void *)gWizardCrackerSweetSpriteTiles, (void *)gWizardCrackerSweetSpriteFrames, NULL, 1 },
};

const u8 g_aWizardCrackerPopItSweetAnims[2][40] = {
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(3, 3), ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(7, 3), ANIM_FRAME(6, 3), ANIM_FRAME(5, 3),
        ANIM_FRAME(6, 3), ANIM_JUMP(0),
    },
};

const u8 g_aWizardCrackerPopItDumbbellAnims[2][18] = {
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(7, 3), ANIM_FRAME(6, 3), ANIM_FRAME(5, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(3, 3), ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_JUMP(0),
    },
};

const u8 g_aWizardCrackerPopItTriangleAnims[2][38] = {
    {
        ANIM_FRAME(9, 0), ANIM_FRAME(8, 3), ANIM_FRAME(7, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(5, 3), ANIM_FRAME(4, 3), ANIM_FRAME(3, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(1, 3), ANIM_FRAME(0, 12), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 0), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3),
        ANIM_FRAME(17, 3), ANIM_FRAME(18, 12), ANIM_FRAME(17, 3), ANIM_FRAME(16, 3),
        ANIM_FRAME(15, 3), ANIM_FRAME(14, 3), ANIM_FRAME(13, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(11, 3), ANIM_FRAME(10, 3), ANIM_JUMP(0),
    },
};

const u8 g_aWizardCrackerPopItOvalAnims[3][22] = {
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_FRAME(4, 3),
        ANIM_FRAME(5, 6), ANIM_FRAME(4, 3), ANIM_FRAME(3, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(1, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3),
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 6), ANIM_FRAME(9, 3), ANIM_FRAME(8, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(6, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3),
        ANIM_FRAME(14, 6), ANIM_FRAME(13, 3), ANIM_FRAME(12, 3), ANIM_FRAME(11, 3),
        ANIM_JUMP(0),
    },
};

const u8 g_aWizardCrackerPopItWrappedAnims[4][20] = {
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 0),
    },
    {
        ANIM_FRAME(11, 0), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3),
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(0, 0),
    },
};

const u8 g_aWizardCrackerPopItPopAnims[WIZARD_CRACKER_POP_IT_KINDS - 1][48] = {
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_SOUND(169), ANIM_FRAME(6, 1),
        ANIM_FRAME(7, 1), ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1),
        ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1),
        ANIM_FRAME(15, 0),
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
        ANIM_FRAME(8, 1), ANIM_SOUND(169), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1),
        ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1),
        ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 0),
    },
    {
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_SOUND(169),
        ANIM_FRAME(7, 1), ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1),
        ANIM_SOUND(169), ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 1),
        ANIM_FRAME(18, 1), ANIM_FRAME(19, 1), ANIM_FRAME(20, 1), ANIM_FRAME(21, 0),
    },
    {
        ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
        ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1), ANIM_FRAME(11, 1),
        ANIM_SOUND(169), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1),
        ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 1), ANIM_FRAME(18, 1),
        ANIM_FRAME(19, 0),
    },
};

const u8 g_aWizardCrackerPopItWrappedPopAnims[2][36] = {
    {
        ANIM_FRAME(24, 3), ANIM_FRAME(25, 3), ANIM_FRAME(26, 2), ANIM_FRAME(27, 1),
        ANIM_FRAME(28, 1), ANIM_FRAME(29, 1), ANIM_FRAME(30, 1), ANIM_FRAME(31, 1),
        ANIM_FRAME(32, 1), ANIM_SOUND(169), ANIM_FRAME(33, 1), ANIM_FRAME(34, 1),
        ANIM_FRAME(35, 1), ANIM_FRAME(36, 1), ANIM_FRAME(37, 1), ANIM_FRAME(38, 1),
        ANIM_FRAME(39, 1), ANIM_FRAME(40, 0),
    },
    {
        ANIM_FRAME(42, 3), ANIM_FRAME(43, 3), ANIM_FRAME(44, 2), ANIM_FRAME(45, 1),
        ANIM_FRAME(46, 1), ANIM_FRAME(47, 1), ANIM_FRAME(48, 1), ANIM_FRAME(49, 1),
        ANIM_SOUND(169), ANIM_FRAME(50, 1), ANIM_FRAME(51, 1), ANIM_FRAME(52, 1),
        ANIM_FRAME(53, 1), ANIM_FRAME(54, 1), ANIM_FRAME(55, 1), ANIM_FRAME(56, 1),
        ANIM_FRAME(57, 1), ANIM_FRAME(58, 0),
    },
};
