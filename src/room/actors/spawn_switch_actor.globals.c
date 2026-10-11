#include "types.h"
#include "overworld/room_actor.h"
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
