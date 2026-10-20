#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "pouring_minigame.h"
#include "gen/graphics/overworld.h"
#include "gen/graphics/minigames/pumpkin.h"

const u8 g_aabServePumpkinJuiceGobletAnims[6][10] = {
    { ANIM_FRAME(0, 0) },
    { ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_JUMP(0) },
    { ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_JUMP(0) },
    { ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_END },
    { ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_END },
    { ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_END },
};

const u8 g_aabServePumpkinJuiceBartenderAnims[4][28] = {
    { ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(2, 3), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_END },
    {
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_FRAME(22, 3), ANIM_FRAME(23, 3),
        ANIM_FRAME(24, 3), ANIM_FRAME(25, 3), ANIM_FRAME(26, 3), ANIM_FRAME(27, 3),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(5, 4), ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4),
        ANIM_FRAME(9, 4), ANIM_FRAME(10, 3), ANIM_FRAME(11, 2), ANIM_FRAME(12, 7),
        ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3),
        ANIM_FRAME(17, 12), ANIM_END,
    },
};

// Rows follow the bartender's action states 1, 2 and 16.
const u8 g_aabServePumpkinJuiceBartenderArmAnims[3][12] = {
    { ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_END },
    { ANIM_FRAME(2, 3), ANIM_FRAME(3, 2), ANIM_FRAME(4, 2), ANIM_END },
    { ANIM_FRAME(5, 4), ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4), ANIM_FRAME(9, 4), ANIM_END },
};

const u8 g_aabServePumpkinJuiceCustomerAnims[5][10] = {
    { ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_JUMP(0) },
    { ANIM_FRAME(3, 8), ANIM_FRAME(4, 6), ANIM_FRAME(5, 6), ANIM_FRAME(6, 6), ANIM_END },
    { ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_JUMP(0) },
    { ANIM_FRAME(3, 4), ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0) },
    { ANIM_FRAME(6, 8), ANIM_FRAME(7, 6), ANIM_FRAME(8, 6), ANIM_FRAME(9, 6), ANIM_END },
};

const u8 g_abServePumpkinJuicePuffAnim[14] = {
    ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 2),
    ANIM_FRAME(4, 2), ANIM_FRAME(5, 2), ANIM_END,
};

const u32 g_adwServePumpkinJuiceCustomerTypeBits[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT] = {
    0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100,
};

// BG1 cells of each lane's tap; the pouring and idle tiles are at (0, 20) and (2, 20) of
// the BG1 graphic.
const IntPoint g_aServePumpkinJuiceTapCells[SERVE_PUMPKIN_JUICE_LANE_COUNT] = {
    { 21, 6 },
    { 23, 11 },
    { 25, 16 },
};

const u32 g_dwServePumpkinJuiceBg0Control = 0x1F03;
const u32 g_dwServePumpkinJuiceBg1Control = 0x1E05;
const u32 g_dwServePumpkinJuiceBg2Control = 0x1D0A;
const u32 g_dwServePumpkinJuiceBg3Control = 0x1C0C;

const ActorGfxRecord g_ServePumpkinJuiceGobletSprite = {
    (void *)gPumpkin001Tiles, (void *)gPumpkin001Frames,
};

const ActorGfxRecord g_ServePumpkinJuiceBartenderSprite = {
    (void *)gPumpkin002Tiles, (void *)gPumpkin002Frames,
};

const ActorGfxRecord g_ServePumpkinJuiceBartenderArmSprite = {
    (void *)gPumpkin003Tiles, (void *)gPumpkin003Frames,
};

const ActorGfxRecord g_ServePumpkinJuicePuffSprite = {
    (void *)gOverworldSpellEffect020Tiles, (void *)gOverworldSpellEffect020Frames,
};

const ActorGfxRecord g_aaServePumpkinJuiceCustomerSprites[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][2] = {
    { { (void *)gPumpkin004Tiles, (void *)gPumpkin004Frames }, { (void *)gPumpkin005Tiles, (void *)gPumpkin005Frames } },
    { { (void *)gPumpkin006Tiles, (void *)gPumpkin006Frames }, { (void *)gPumpkin007Tiles, (void *)gPumpkin007Frames } },
    { { (void *)gPumpkin008Tiles, (void *)gPumpkin008Frames }, { (void *)gPumpkin009Tiles, (void *)gPumpkin009Frames } },
    { { (void *)gPumpkin010Tiles, (void *)gPumpkin010Frames }, { (void *)gPumpkin011Tiles, (void *)gPumpkin011Frames } },
    { { (void *)gPumpkin012Tiles, (void *)gPumpkin012Frames }, { (void *)gPumpkin013Tiles, (void *)gPumpkin013Frames } },
    { { (void *)gPumpkin014Tiles, (void *)gPumpkin014Frames }, { (void *)gPumpkin015Tiles, (void *)gPumpkin015Frames } },
    { { (void *)gPumpkin016Tiles, (void *)gPumpkin016Frames }, { (void *)gPumpkin017Tiles, (void *)gPumpkin017Frames } },
    { { (void *)gPumpkin018Tiles, (void *)gPumpkin018Frames }, { (void *)gPumpkin019Tiles, (void *)gPumpkin019Frames } },
    { { (void *)gPumpkin020Tiles, (void *)gPumpkin020Frames }, { (void *)gPumpkin021Tiles, (void *)gPumpkin021Frames } },
};

const u8 g_abServePumpkinJuiceCustomerPaletteCounts[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT] = {
    1, 1, 2, 3, 2, 2, 1, 1, 1,
};

const ObjPalette *const g_aapServePumpkinJuiceCustomerPalettes[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][4] = {
    { (const ObjPalette *)gPumpkin021Palette, (const ObjPalette *)gPumpkin022Palette },
    { (const ObjPalette *)gPumpkin023Palette, (const ObjPalette *)gPumpkin024Palette },
    { (const ObjPalette *)gPumpkin025Palette, (const ObjPalette *)gPumpkin026Palette, (const ObjPalette *)gPumpkin027Palette },
    {
        (const ObjPalette *)gPumpkin028Palette, (const ObjPalette *)gPumpkin029Palette,
        (const ObjPalette *)gPumpkin030Palette, (const ObjPalette *)gPumpkin031Palette,
    },
    { (const ObjPalette *)gPumpkin032Palette, (const ObjPalette *)gPumpkin033Palette, (const ObjPalette *)gPumpkin034Palette },
    { (const ObjPalette *)gPumpkin035Palette, (const ObjPalette *)gPumpkin036Palette, (const ObjPalette *)gPumpkin037Palette },
    { (const ObjPalette *)gPumpkin038Palette, (const ObjPalette *)gPumpkin039Palette },
    { (const ObjPalette *)gPumpkin040Palette, (const ObjPalette *)gPumpkin041Palette },
    { (const ObjPalette *)gPumpkin042Palette, (const ObjPalette *)gPumpkin043Palette },
};

const ActorGfxRecord *const g_aapServePumpkinJuiceCustomerSpriteRows[SERVE_PUMPKIN_JUICE_CUSTOMER_TYPE_COUNT][2] = {
    { &g_aaServePumpkinJuiceCustomerSprites[0][0], &g_aaServePumpkinJuiceCustomerSprites[0][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[1][0], &g_aaServePumpkinJuiceCustomerSprites[1][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[2][0], &g_aaServePumpkinJuiceCustomerSprites[2][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[3][0], &g_aaServePumpkinJuiceCustomerSprites[3][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[4][0], &g_aaServePumpkinJuiceCustomerSprites[4][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[5][0], &g_aaServePumpkinJuiceCustomerSprites[5][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[6][0], &g_aaServePumpkinJuiceCustomerSprites[6][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[7][0], &g_aaServePumpkinJuiceCustomerSprites[7][1] },
    { &g_aaServePumpkinJuiceCustomerSprites[8][0], &g_aaServePumpkinJuiceCustomerSprites[8][1] },
};
