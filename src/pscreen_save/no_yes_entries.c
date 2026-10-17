#include "types.h"
#include "pscreen_save.h"

// The rows of the No/Yes prompts: the save confirmation, the new game slot
// confirmation and ConfirmTradeScreen.
const ListMenuEntry g_aNoYesEntries[2] = {
    { 3, 0x543, 1 },  // "No"
    { 0, 0x542, 0 },  // "Yes"
};
