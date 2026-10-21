#include "trigger_actor.h"
#include "actor_anim.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_aRoomSwitchSprites[5] = {
    { (void *)gButtonTiles, (void *)gButtonFrames },
    { (void *)gPressurePlateTiles, (void *)gPressurePlateFrames },
    { (void *)gLever001Tiles, (void *)gLever001Frames },
    { (void *)gLever002Tiles, (void *)gLever002Frames },
    { (void *)gLever003Tiles, (void *)gLever003Frames },
};

// Indexed by the actor's character id, 0-10; both lists end with NULL.
const ActorGfxRecord *const g_apRoomSwitchAssetRecords[12] = {
    &g_aRoomSwitchSprites[1],
    &g_aRoomSwitchSprites[1],
    &g_aRoomSwitchSprites[1],
    &g_aRoomSwitchSprites[0],
    &g_aRoomSwitchSprites[0],
    &g_aRoomSwitchSprites[0],
    &g_aRoomSwitchSprites[2],
    &g_aRoomSwitchSprites[3],
    &g_aRoomSwitchSprites[4],
    &g_aRoomSwitchSprites[3],
    &g_aRoomSwitchSprites[2],
    NULL,
};

const void *const g_apRoomSwitchEffectData[12] = {
    gLever003Palette,
    gLever003Palette,
    gLever003Palette,
    gButtonPalette,
    gButtonPalette,
    gButtonPalette,
    gActorSprite2_123Palette,
    gActorSprite2_124Palette,
    gActorSprite2_125Palette,
    gActorSprite2_124Palette,
    gActorSprite2_123Palette,
    NULL,
};

// Per character id like the tables above; the switch code steps frames
// itself and no reader of these streams was found.
const u8 g_aabUnusedRoomSwitchAnims[12][20] = {
    { ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_FRAME(0, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_FRAME(0, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_FRAME(0, 1), ANIM_END },
    { ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_EVENT(0),
      ANIM_FRAME(6, 1), ANIM_FRAME(5, 1), ANIM_FRAME(4, 1), ANIM_END },
    { ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_EVENT(0),
      ANIM_FRAME(6, 1), ANIM_FRAME(5, 1), ANIM_FRAME(4, 1), ANIM_END },
    { ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_EVENT(0),
      ANIM_FRAME(6, 1), ANIM_FRAME(5, 1), ANIM_FRAME(4, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_END },
    { ANIM_FRAME(0, 1), ANIM_EVENT(0), ANIM_FRAME(1, 1), ANIM_END },
    { 0 },
};
