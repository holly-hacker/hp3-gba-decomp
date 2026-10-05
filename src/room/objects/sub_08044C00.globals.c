#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomSwitchSprites[5] = {
    { (void *)gButtonTiles, (void *)gButtonFrames },
    { (void *)gPressurePlateTiles, (void *)gPressurePlateFrames },
    { (void *)gLever001Tiles, (void *)gLever001Frames },
    { (void *)gLever002Tiles, (void *)gLever002Frames },
    { (void *)gLever003Tiles, (void *)gLever003Frames },
};

// Indexed by the object's character id, 0-10; both lists end with NULL.
const ObjectGfxRecord *const g_apRoomSwitchAssetRecords[12] = {
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
    gObjectSprite2_123Palette,
    gObjectSprite2_124Palette,
    gObjectSprite2_125Palette,
    gObjectSprite2_124Palette,
    gObjectSprite2_123Palette,
    NULL,
};
