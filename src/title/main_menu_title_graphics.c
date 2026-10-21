#include "types.h"
#include "title.h"
#ifdef VERSION_JP
#include "gen/graphics/menus/jp.h"
#else
#include "gen/graphics/menus/us.h"
#endif

#ifdef VERSION_JP
// The JP main menu draws no title graphic, so nothing reads this entry.
const u8 *const g_apMainMenuTitleGraphic[MAIN_MENU_TITLE_COUNT] = {
    gUnusedMainMenuTitleGraphic,
};
#else
// The title graphic per Language; both English versions share one.
const u8 *const g_apMainMenuTitleGraphic[MAIN_MENU_TITLE_COUNT] = {
    gMainMenuTitleEnglish,  // English (US)
    gMainMenuTitleEnglish,  // English (GB)
    gMainMenuTitleFrench,  // French
    gMainMenuTitleGerman,  // German
    gMainMenuTitleSpanish,  // Spanish
    gMainMenuTitleItalian,  // Italian
    gMainMenuTitleDutch,  // Dutch
    gMainMenuTitleDanish,  // Danish
};
#endif
