#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "buckbeak_minigame.h"
#include "char_block.h"
#include "video.h"

const u32 g_dwBuckbeakMinigameBg2Control = 0xF881;
const u32 g_dwBuckbeakMinigameBg1Control = 0x760A;
const u32 g_dwBuckbeakMinigameBg0Control = 0x3507;
const u32 g_dwBuckbeakMinigameBg2GroundControl = 0x3506;

const ActorAssetRecord g_aBuckbeakMinigameBuckbeakAssets[3] = {
    { (void *)gBuckbeakMinigameBuckbeakTiles, (void *)gBuckbeakMinigameBuckbeakFrames, 0, 0 },
    { (void *)gBuckbeakMinigameBuckbeakTurningTiles, (void *)gBuckbeakMinigameBuckbeakTurningFrames, 0, 0 },
    { (void *)gBuckbeakMinigameBuckbeakTurningTiles, (void *)gBuckbeakMinigameBuckbeakTurningFrames, 0, 0 },
};

// The wing beat sound plays on frame 6.
const u8 g_abBuckbeakMinigameFlyAnimData[32] = {
    ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
    ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_SOUND(0x3A), ANIM_FRAME(6, 2),
    ANIM_FRAME(7, 2), ANIM_FRAME(8, 2), ANIM_FRAME(9, 2), ANIM_FRAME(10, 2),
    ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_JUMP(0),
};

const ActorAssetRecord g_BuckbeakMinigameRingAsset = {
    (void *)gBuckbeakMinigameBatTiles, (void *)gBuckbeakMinigameBatFrames, 0, 0
};

const void *const g_aapBuckbeakMinigameBgGraphics[3][2] = {
    { gBuckbeakMinigameEasyBg1Graphic, gBuckbeakMinigameEasyBg0Graphic },
    { gBuckbeakMinigameMediumBg1Graphic, gBuckbeakMinigameMediumBg0Graphic },
    { gBuckbeakMinigameHardBg1Graphic, gBuckbeakMinigameHardBg0Graphic },
};

const u8 g_abBuckbeakMinigameRingAnimData[28] = {
    ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
    ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1), ANIM_FRAME(11, 1),
    ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
};

// The ground starts below line 0x3F and the sky resumes at line 0xA0.
const ScanlineEffectEntry g_aBuckbeakMinigameScanlineEffects[2] = {
    { 0x3F, 0, 0, 0, BeginBuckbeakMinigameGroundScanline },
    { 0xA0, 0, 0, 0, EndBuckbeakMinigameGroundScanline },
};

const BuckbeakMinigameWorldPos g_aBuckbeakMinigameRingPositions[BUCKBEAK_MINIGAME_RING_COUNT] = {
    { { 0x1280000, 0x1580000 }, 0x820000 },
    { { 0x2380000, 0x16E0000 }, 0x500000 },
    { { 0x3600000, 0x1D70000 }, 0xBE0000 },
    { { 0x3D70000, 0x2CF0000 }, 0xA00000 },
    { { 0x33E0000, 0x3B00000 }, 0x280000 },
    { { 0x2380000, 0x3EF0000 }, 0xE60000 },
    { { 0x1200000, 0x3900000 }, 0x820000 },
    { { 0x780000, 0x2C80000 }, 0x3C0000 },
    { { 0x800000, 0x1E80000 }, 0xBE0000 },
};

// BG2's lake water animation: ripples in the eight tiles every lake is made of, registered with g_dwBuckbeakMinigameBg2Control.
const BgTileAnimation16 g_BuckbeakMinigameWaterAnimation = {
    2, 16, 0, 0x200,
    {
        { gBuckbeakMinigameWaterFrame001, 3 },
        { gBuckbeakMinigameWaterFrame002, 3 },
        { gBuckbeakMinigameWaterFrame003, 3 },
        { gBuckbeakMinigameWaterFrame004, 3 },
        { gBuckbeakMinigameWaterFrame005, 3 },
        { gBuckbeakMinigameWaterFrame006, 3 },
        { gBuckbeakMinigameWaterFrame007, 3 },
        { gBuckbeakMinigameWaterFrame008, 3 },
        { gBuckbeakMinigameWaterFrame009, 3 },
        { gBuckbeakMinigameWaterFrame010, 3 },
        { gBuckbeakMinigameWaterFrame011, 3 },
        { gBuckbeakMinigameWaterFrame012, 3 },
        { gBuckbeakMinigameWaterFrame013, 3 },
        { gBuckbeakMinigameWaterFrame014, 3 },
        { gBuckbeakMinigameWaterFrame015, 3 },
        { gBuckbeakMinigameWaterFrame016, 3 },
    },
};
