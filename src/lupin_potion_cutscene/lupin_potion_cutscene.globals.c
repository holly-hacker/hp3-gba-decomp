#include "types.h"
#include "actor_anim.h"
#include "lupin_potion_cutscene.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_LupinPotionShadowGfx = {
    (void *)gActorShadowTiles, (void *)gActorShadowFrames,
};

const ScanlineEffectEntry g_aLupinPotionScanlineTable[2] = {
    { 120, 0, 1, 0, LupinPotionPanelScanlineCallback },
    { 159, 0, 0, 0, LupinPotionPanelScanlineCallback },
};

const u32 g_dwLupinPotionBg3Control = 0x4603;
const u32 g_dwLupinPotionBg1Control = 0x5E07;
const u32 g_dwLupinPotionTextBgControl = 0x560B;  // BG2
const u32 g_dwLupinPotionBg0Control = 0x0F0F;

const LupinPotionDialogLine g_aLupinPotionDialog[2][LUPIN_POTION_DIALOG_PAGE_LINES] = {
    {
        { 0x35F, 3 },  // "Oh my - Professor Lupin didn't take his Potion tonight!"
        { 0x361, 1 },  // "Leave it to me - GO!"
    },
    {
        { 0x362, 4 },  // "Sirius!"
        { 0x363, 5 },  // "Grrrr…."
    },
};

// Pixels.
const IntPoint g_aLupinPotionCastPositions[LUPIN_POTION_CAST_COUNT] = {
    { 20, 150 },
    { 80, 150 },
    { -40, 150 },
    { 100, 150 },
    { 50, 150 },
    { 120, 150 },
};

const ActorAssetRecord g_aLupinPotionCastAssets[LUPIN_POTION_CAST_COUNT] = {
    { (void *)gActorSprite2_005Tiles, (void *)gActorSprite2_005Frames, (const ObjPalette *)gActorSprite2_005Palette },
    { (void *)gActorSprite2_006Tiles, (void *)gActorSprite2_006Frames, (const ObjPalette *)gActorSprite2_006Palette },
    { (void *)gActorSprite2_007Tiles, (void *)gActorSprite2_007Frames, (const ObjPalette *)gActorSprite2_007Palette },
    { (void *)gHarryWalkTiles, (void *)gHarryWalkFrames, (const ObjPalette *)gHarryWalkPalette },
    { (void *)gActorSprite2_008Tiles, (void *)gActorSprite2_008Frames, (const ObjPalette *)gActorSprite2_008Palette },
    { (void *)gActorSprite2_009Tiles, (void *)gActorSprite2_009Frames, (const ObjPalette *)gActorSprite2_009Palette },
};

const ActorAssetRecord g_aLupinPotionPose4Assets[5] = {
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames, (const ObjPalette *)gOverworldPlayer001Palette },
    { (void *)gActorSprite2_010Tiles, (void *)gActorSprite2_010Frames, (const ObjPalette *)gActorSprite2_010Palette },
    { (void *)gActorSprite2_011Tiles, (void *)gActorSprite2_011Frames, (const ObjPalette *)gActorSprite2_011Palette },
    { (void *)gActorSprite2_012Tiles, (void *)gActorSprite2_012Frames, (const ObjPalette *)gActorSprite2_012Palette },
    { (void *)gActorSprite2_013Tiles, (void *)gActorSprite2_013Frames, (const ObjPalette *)gActorSprite2_013Palette },
};

const ActorAssetRecord g_aLupinPotionPoseAssets[3][3] = {
    {
        { (void *)gActorSprite2_005Tiles, (void *)gActorSprite2_005Frames, (const ObjPalette *)gActorSprite2_005Palette },
        { (void *)gActorSprite2_006Tiles, (void *)gActorSprite2_006Frames, (const ObjPalette *)gActorSprite2_006Palette },
        { (void *)gActorSprite2_007Tiles, (void *)gActorSprite2_007Frames, (const ObjPalette *)gActorSprite2_007Palette },
    },
    {
        { (void *)gActorSprite2_014Tiles, (void *)gActorSprite2_014Frames, (const ObjPalette *)gActorSprite2_014Palette },
        { (void *)gActorSprite2_015Tiles, (void *)gActorSprite2_015Frames, (const ObjPalette *)gActorSprite2_015Palette },
        { (void *)gActorSprite2_016Tiles, (void *)gActorSprite2_016Frames, (const ObjPalette *)gActorSprite2_016Palette },
    },
    {
        { (void *)gActorSprite2_017Tiles, (void *)gActorSprite2_017Frames, (const ObjPalette *)gActorSprite2_017Palette },
        { (void *)gActorSprite2_018Tiles, (void *)gActorSprite2_018Frames, (const ObjPalette *)gActorSprite2_018Palette },
        { (void *)gActorSprite2_019Tiles, (void *)gActorSprite2_019Frames, (const ObjPalette *)gActorSprite2_019Palette },
    },
};

const ActorAssetRecord g_aLupinPotionPanelAssets[6] = {
    { (void *)gActorSprite016Tiles, (void *)gActorSprite016Frames, (const ObjPalette *)gActorSprite016Palette },
    { (void *)gChathead004Tiles, (void *)gChathead004Frames, (const ObjPalette *)gChathead004Palette },
    { (void *)gPortrait039Tiles, (void *)gPortrait039Frames, (const ObjPalette *)gPortrait039Palette },
    { (void *)gPortrait013Tiles, (void *)gPortrait013Frames, (const ObjPalette *)gPortrait013Palette },
    { (void *)gPortrait001Tiles, (void *)gPortrait001Frames, (const ObjPalette *)gPortrait001Palette },
    { (void *)gChathead005Tiles, (void *)gChathead005Frames, (const ObjPalette *)gChathead005Palette },
};

const ActorAssetRecord g_aLupinPotionEffectAssets[2] = {
    { (void *)gOverworldSpellEffect001Tiles, (void *)gOverworldSpellEffect001Frames, (const ObjPalette *)gOverworldSpellEffect001Palette },
    { (void *)gActorSprite2_016Tiles, (void *)gActorSprite2_016Frames, (const ObjPalette *)gActorSprite2_016Palette },
};

const u8 g_abLupinPotionStandFrames[4] = { 4, 2, 0, 2 };

const u8 g_aLupinPotionWalkAnims[4][24] = {
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
};

const u8 g_aLupinPotionPose4Anims[5][62] = {
    {
        ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 12), ANIM_FRAME(12, 3), ANIM_END,
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_SOUND(103), ANIM_FRAME(10, 3), ANIM_END,
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_END,
    },
    {
        ANIM_SOUND(76), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_SOUND(54),
        ANIM_FRAME(2, 50), ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3),
        ANIM_FRAME(6, 3), ANIM_END,
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_SOUND(164), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(0, 3),
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3),
        ANIM_FRAME(26, 3), ANIM_FRAME(27, 3), ANIM_END,
    },
};

const u8 g_aLupinPotionPose1Anims[3][36] = {
    {
        ANIM_SOUND(76), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_SOUND(52), ANIM_END,
    },
    {
        ANIM_SOUND(76), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_SOUND(53), ANIM_END,
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_END,
    },
};

const u8 g_aLupinPotionPose2WalkAnims[3][24] = {
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
        ANIM_FRAME(8, 3), ANIM_JUMP(0),
    },
};

const u8 g_aLupinPotionPose2StandAnims[3][24] = {
    { ANIM_FRAME(1, 3), ANIM_JUMP(0), },
    { ANIM_FRAME(1, 3), ANIM_JUMP(0), },
    { ANIM_FRAME(0, 3), ANIM_JUMP(0), },
};

const u8 g_aLupinPotionWalkBackAnims[4][24] = {
    {
        ANIM_FRAME(28, 3), ANIM_FRAME(27, 3), ANIM_FRAME(26, 3), ANIM_FRAME(25, 3),
        ANIM_FRAME(24, 3), ANIM_FRAME(23, 3), ANIM_FRAME(22, 3), ANIM_FRAME(21, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(20, 3), ANIM_FRAME(19, 3), ANIM_FRAME(18, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(16, 3), ANIM_FRAME(15, 3), ANIM_FRAME(14, 3), ANIM_FRAME(13, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(12, 3), ANIM_FRAME(11, 3), ANIM_FRAME(10, 3), ANIM_FRAME(9, 3),
        ANIM_FRAME(8, 3), ANIM_FRAME(7, 3), ANIM_FRAME(6, 3), ANIM_FRAME(5, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(20, 3), ANIM_FRAME(19, 3), ANIM_FRAME(18, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(16, 3), ANIM_FRAME(15, 3), ANIM_FRAME(14, 3), ANIM_FRAME(13, 3),
        ANIM_JUMP(0),
    },
};

const u8 g_aLupinPotionEffectAnims[2][62] = {
    {
        ANIM_FRAME(12, 30), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3),
        ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3),
        ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3),
        ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_END,
    },
    {
        ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 200), ANIM_END,
    },
};
