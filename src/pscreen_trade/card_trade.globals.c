#include "types.h"
#include "pscreen_trade.h"
#include "gen/graphics/overworld.h"

const ListMenuEntry g_aCardTradeEntries[3] = {
    { FolioUniversitas, 0x8C7, 1 },  // "Choose Card"
    { 0,                0x8C8, 0 },  // "Trade Cards"
    { Connectivity,     0x8C9, 0 },  // "Exit"
};

const ListMenuDefinition g_CardTradeMenuDefinition = {
    0x538,  // title: "Trade Cards"
    ARRAY_COUNT(g_aCardTradeEntries),
    2,
    { 24, 104 },
    { 0, 12 },
    g_aCardTradeEntries,
    0,
    { 0, 0 },
    0,
    { -8, 4 },
};

const CardTradeSlotPosition g_aCardTradeSlotPositions[2] = {
    { 0x18, 0x26 },
    { 0x90, 0x26 },
};

const ActorAssetRecord g_aCardTradeReadyIconAssets[2] = {
    { (void *)gActorSprite031Tiles, (void *)gActorSprite031Frames, (void *)gActorSprite096Palette, 0 },
    { (void *)gActorSprite032Tiles, (void *)gActorSprite032Frames, (void *)gActorSprite097Palette, 0 },
};
