#include "types.h"
#include "menu/connectivity.h"

// Row 0 backs out to Connectivity, row 1 continues to CardTrade; the modes in the
// entries are not read.
const ListMenuEntry g_aConfirmTradeEntries[2] = {
    { 3, 0x543, 0, 1 },  // "No"
    { 0, 0x542, 0, 0 },  // "Yes"
};
