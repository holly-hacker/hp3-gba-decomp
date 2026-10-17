#include "types.h"
#include "pause_menu.h"
#include "pscreen_save.h"

const ListMenuDefinition g_SaveConfirmationMenuDefinition = {
    0x533,  // title: "Save Game"
    2,
    2,
    { 112, 80 },
    { 0, 12 },
    g_aNoYesEntries,
    0,
    { 0, 0 },
    0,
    { -16, 3 },
};
