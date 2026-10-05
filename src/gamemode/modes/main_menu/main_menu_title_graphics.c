#include "types.h"
#include "menu/main_menu.h"
#include "gen/graphics/menus/us.h"

// The title graphic per Language; both English versions share one. The JP
// build has no localized title.
const u8 *const g_apMainMenuTitleGraphic[8] = {
    gMainMenuTitleEnglish,  // English (US)
    gMainMenuTitleEnglish,  // English (GB)
    gMainMenuTitleFrench,  // French
    gMainMenuTitleGerman,  // German
    gMainMenuTitleSpanish,  // Spanish
    gMainMenuTitleItalian,  // Italian
    gMainMenuTitleDutch,  // Dutch
    gMainMenuTitleDanish,  // Danish
};
