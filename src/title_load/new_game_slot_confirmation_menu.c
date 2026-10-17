#include "types.h"
#include "pause_menu.h"
#include "pscreen_save.h"
#include "title_load.h"

const ListMenuDefinition g_NewGameSlotConfirmationMenuDefinition = {
    0x8CD,  // title: "New Game"
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
