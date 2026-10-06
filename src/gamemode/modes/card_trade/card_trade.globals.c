#include "types.h"
#include "menu/card_trade.h"

const ListMenuEntry g_aCardTradeEntries[3] = {
    { FolioUniversitas, 0x8C7, 0, 1 },  // "Choose Card"
    { 0,                0x8C8, 0, 0 },  // "Trade Cards"
    { Connectivity,     0x8C9, 0, 0 },  // "Exit"
};

const ListMenuDefinition g_CardTradeMenuDefinition = {
    0x538,  // title: "Trade Cards"
    ARRAY_COUNT(g_aCardTradeEntries),
    2,
    0,
    24, 104,
    0, 12,
    g_aCardTradeEntries,
    0,
    0,
    0, 0,
    0,
    -8, 4,
};

const CardTradeSlotPosition g_aCardTradeSlotPositions[2] = {
    { 0x18, 0x26 },
    { 0x90, 0x26 },
};
