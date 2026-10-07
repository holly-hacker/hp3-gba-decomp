#include "types.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "gen/graphics/overworld.h"
#include "menu/unused_hogwarts_map_screen.h"

const u8 *const g_apUnusedHogwartsMapBackgrounds[UNUSED_HOGWARTS_MAP_ENTRY_COUNT] = {
    gHippogriffLanguageMinigameBgs002,
    gHippogriffLanguageMinigameBgs003,
    gHippogriffLanguageMinigameBgs004,
    gHippogriffLanguageMinigameBgs005,
    gHippogriffLanguageMinigameBgs006,
    gHippogriffLanguageMinigameBgs007,
    gHippogriffLanguageMinigameBgs008,
    gHippogriffLanguageMinigameBgs009,
    gHippogriffLanguageMinigameBgs010,
};

const u32 g_dwUnusedHogwartsMapBg0Control = 0x1F01;
const u32 g_dwUnusedHogwartsMapBg1Control = 0x1E00;
const u32 g_dwUnusedHogwartsMapBg2Control = 0xD902;
const u32 g_dwUnusedHogwartsMapBg3Control = 0x1D0B;

const ObjectGfxRecord g_UnusedHogwartsMapEntryGfx = {
    (void *)gObjectSprite015Tiles,
    (void *)gObjectSprite015Frames,
};
