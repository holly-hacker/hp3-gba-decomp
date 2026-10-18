#include "pscreen_gamecube.h"
#include "gen/graphics/overworld.h"

const ListMenuDefinition g_GameCubeLinkMenuDefinition = {
    0x650,  // title: "Nintendo GameCube™ Link"
};

const ActorAssetRecord g_aGameCubeLinkIconAssets[3] = {
    { (void *)gGameCubeLinkGameCubeTiles, (void *)gGameCubeLinkGameCubeFrames, (void *)gGameCubeLinkGameCubePalette, 0 },
    { (void *)gGameCubeLinkGameBoyAdvanceTiles, (void *)gGameCubeLinkGameBoyAdvanceFrames, (void *)gGameCubeLinkGameBoyAdvancePalette, 0 },
    { (void *)gGameCubeLinkArrowsTiles, (void *)gGameCubeLinkArrowsFrames, (void *)gGameCubeLinkArrowsPalette, 0 },
};

const GameCubeLinkIconPosition g_aGameCubeLinkIconPositions[3] = {
    { 0x30, 0x52 },
    { 0xC0, 0x52 },
    { 0x78, 0x32 },
};

const GameCubeLinkText g_aGameCubeLinkResultTexts[7] = {
    { 0x653, 0 },     // JOYBUS_STATE_IDLE: "Waiting for connection."
    { 0x654, 0 },     // JOYBUS_STATE_CONNECTED: "Connected."
    { 0x655, 0 },     // JOYBUS_STATE_RECEIVING: "Receiving data."
    { 0x656, 0 },     // JOYBUS_STATE_SENDING: "Sending data."
    { 0x657, 60 },    // JOYBUS_STATE_RECEIVED: "Receive complete."
    { 0x654, 0 },     // JOYBUS_STATE_SENT: "Connected."
    { 0x659, 60 },    // JOYBUS_STATE_ERROR: "Connection failed!"
};

const GameCubeLinkText g_aGameCubeLinkStatusTexts[4] = {
    { 0xACF, 0 },  // no text
    { 0x65B, 0 },  // "Owl Care Kit received!"
    { 0x65C, 0 },  // "Your owl is ready to race!"
    { 0x65D, 0 },  // "Press the A Button to return to the Owl Care Kit."
};
