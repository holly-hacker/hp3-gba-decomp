#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "graphics.h"
#include "hippogriff_glide.h"
#include "main_menu.h"
#include "mem.h"

void InitializeHippogriffGlideMinigame(void)
{
    g_pHippogriffGlide = AllocZeroed(sizeof(HippogriffGlideState));
    ClearResourceCacheSlots();
    sub_0803094C(0);
    sub_0800D264((void *)g_MainMenuPalette, 0, 0x10);
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
