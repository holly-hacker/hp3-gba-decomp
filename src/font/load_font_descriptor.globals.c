#include "types.h"
#include "font.h"
#include "gen/graphics/menus.h"
#ifdef VERSION_JP
#include "gen/graphics/menus/jp.h"
#endif

#ifdef VERSION_JP
const FontTableEntry g_aExtFontTable[12] = {
    { gKanjiFont00, 9 },
    { gKanjiFont00, 9 },
    { gKanjiFont00, 9 },
    { gKanjiFont01, 16 },
    { gKanjiFont01, 16 },
    { gKanjiFont02, 16 },
    { gKanjiFont02, 16 },
    { gKanjiFont00, 9 },
    { gKanjiFont00, 9 },
    { gKanjiFont00, 9 },
    { gKanjiFont01, 12 },
    { gKanjiFont03, 8 },
};
#endif

const FontTableEntry g_aFontTable[12] = {
    { gTextFont00, 8 },
    { gTextFont01, 8 },
    { gTextFont02, 8 },
    { gTextFont03, 16 },
    { gTextFont04, 16 },
    { gTextFont05, 13 },
    { gTextFont06, 16 },
    { gTextFont07, 8 },
    { gTextFont08, 8 },
    { gTextFont09, 8 },
#ifdef VERSION_JP
    { gTextFont05, 12 },
#else
    { gTextFont07, 12 },
#endif
    { gTextFont09, 8 },
};
