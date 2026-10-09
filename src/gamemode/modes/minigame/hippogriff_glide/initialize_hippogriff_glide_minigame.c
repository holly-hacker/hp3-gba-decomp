#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "minigame/hippogriff_glide.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "gen/graphics/menus.h"

void InitializeHippogriffGlideMinigame(void)
{
    g_pHippogriffGlide = AllocZeroed(sizeof(HippogriffGlideState));
    ClearResourceCacheSlots();
    sub_0803094C(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    sub_08009E1C();
    PlayMusicModule(0x30);
    g_pHippogriffGlide->dwScore = 0;
    sub_0800907C();
    sub_08008E88();
    g_GameModeStackContext.dwModeState = HippogriffGlideStateFlying;
    g_adwHippogriffGlideUnk[0] = 0;
    g_adwHippogriffGlideUnk[1] = 0;
    g_adwHippogriffGlideUnk[2] = 0;
    g_pHippogriffGlide->dwUnk10 = 0;
    sub_08009D8C();
    sub_0800975C();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
