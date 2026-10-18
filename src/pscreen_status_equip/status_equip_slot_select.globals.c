#include "actor.h"
#include "actor_anim.h"
#include "pscreen_status_equip.h"
#include "gen/graphics/overworld.h"

const ActorAssetRecord g_StatusEquipSlotFrameAsset = {
    (void *)gActorSprite094Tiles, (void *)gActorSprite094Frames, (void *)gActorSprite094Palette, 0,
};

const void *const g_pStatusEquipSlotFramePalette = gActorSprite094Palette;

const ActorAssetRecord g_StatusEquipSlotCursorAsset = {
    (void *)gStatusEquipSlotCursorTiles, (void *)gStatusEquipSlotCursorFrames,
    (void *)gStatusEquipSlotCursorPalette, 0,
};

const void *const g_pStatusEquipSlotCursorPalette = gStatusEquipSlotCursorPalette;

// The cursor pulses over a slot that has something to equip and dims over one that does not.
const u8 g_abStatusEquipSlotCursorPulseAnim[14] = {
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_JUMP(0),
};

const u8 g_abStatusEquipSlotCursorDimAnim[2] = { ANIM_FRAME(7, 0) };

// One full turn of the chosen party member, 32 frames.
const u8 g_abStatusCharacterSpinAnim[66] = {
    ANIM_FRAME(0, 2),  ANIM_FRAME(1, 3),  ANIM_FRAME(2, 2),  ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 2),  ANIM_FRAME(5, 3),  ANIM_FRAME(6, 2),  ANIM_FRAME(7, 3),
    ANIM_FRAME(8, 2),  ANIM_FRAME(9, 3),  ANIM_FRAME(10, 2), ANIM_FRAME(11, 3),
    ANIM_FRAME(12, 2), ANIM_FRAME(13, 3), ANIM_FRAME(14, 2), ANIM_FRAME(15, 3),
    ANIM_FRAME(16, 2), ANIM_FRAME(17, 3), ANIM_FRAME(18, 2), ANIM_FRAME(19, 3),
    ANIM_FRAME(20, 2), ANIM_FRAME(21, 3), ANIM_FRAME(22, 2), ANIM_FRAME(23, 3),
    ANIM_FRAME(24, 2), ANIM_FRAME(25, 3), ANIM_FRAME(26, 2), ANIM_FRAME(27, 3),
    ANIM_FRAME(28, 2), ANIM_FRAME(29, 3), ANIM_FRAME(30, 2), ANIM_FRAME(31, 3),
    ANIM_JUMP(0),
};
