#include "types.h"
#include "graphics/object.h"
#include "graphics/object_anim.h"
#include "minigame/divination_tea.h"
#include "gen/graphics/overworld.h"

// Command 0 holds the first frame; the cups play from command 1 once B is
// pressed and stop on their last frame.
const u8 g_DivinationTeaCupAnimData[68] = {
    ANIM_FRAME(0, 0),
    ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4), ANIM_FRAME(4, 4),
    ANIM_FRAME(5, 4), ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4),
    ANIM_FRAME(9, 4), ANIM_FRAME(10, 4), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4),
    ANIM_FRAME(13, 4), ANIM_FRAME(14, 4), ANIM_FRAME(15, 4), ANIM_FRAME(16, 4),
    ANIM_FRAME(17, 4), ANIM_FRAME(18, 4), ANIM_FRAME(19, 4), ANIM_FRAME(20, 4),
    ANIM_FRAME(21, 4), ANIM_FRAME(22, 4), ANIM_FRAME(23, 4), ANIM_FRAME(24, 4),
    ANIM_FRAME(25, 4), ANIM_FRAME(26, 4), ANIM_FRAME(27, 4), ANIM_FRAME(28, 4),
    ANIM_FRAME(29, 4), ANIM_FRAME(30, 4), ANIM_FRAME(31, 4), ANIM_FRAME(32, 4),
    ANIM_FRAME(33, 0),
};

const u32 g_dwDivinationTeaBg2Control = 0x7F83;
const u32 g_dwDivinationTeaBg0Control = 0x1E0C;
const u32 g_dwDivinationTeaBg1Control = 0x1C86;

const ObjectGfxRecord g_DivinationTeaLeafSprite = {
    (void *)gDivinationTeaLeafTiles, (void *)gDivinationTeaLeafFrames,
};

const ObjectGfxRecord g_DivinationTeaCupSprite = {
    (void *)gDivinationTeaCupTiles, (void *)gDivinationTeaCupFrames,
};

const ObjectAssetRecord g_DivinationTeaTextFrameAsset = {
    (void *)gDivinationTeaTextFrameTiles, (void *)gDivinationTeaTextFrameFrames, (void *)gDivinationTeaTextFramePalette, 0,
};
