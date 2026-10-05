#include "types.h"
#include "menu/main_menu.h"
#include "gen/graphics/menus/us.h"

// The title graphic per Language; both English versions share one. The JP
// build has no localized title.
const u8 *const g_apMainMenuTitleGraphic[8] = {
    gMainMenuTitles001,  // English (US)
    gMainMenuTitles001,  // English (GB)
    gMainMenuTitles002,  // French
    gMainMenuTitles003,  // German
    gMainMenuTitles004,  // Spanish
    gMainMenuTitles005,  // Italian
    gMainMenuTitles006,  // Dutch
    gMainMenuTitles007,  // Danish
};
