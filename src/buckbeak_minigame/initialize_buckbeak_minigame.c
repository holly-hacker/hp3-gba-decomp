#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "buckbeak_minigame.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "gen/graphics/menus.h"

void InitializeBuckbeakMinigame(void)
{
    g_pBuckbeakMinigame = AllocZeroed(sizeof(BuckbeakMinigameState));
    ClearObjPaletteSlots();
    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    sub_08009E1C();
    PlayMusicModule(0x30);
    g_pBuckbeakMinigame->dwScore = 0;
    sub_0800907C();
    sub_08008E88();
    g_GameModeStackContext.dwModeState = BuckbeakMinigameStateFlying;
    g_adwBuckbeakMinigameUnk[0] = 0;
    g_adwBuckbeakMinigameUnk[1] = 0;
    g_adwBuckbeakMinigameUnk[2] = 0;
    g_pBuckbeakMinigame->dwUnk10 = 0;
    sub_08009D8C();
    sub_0800975C();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
