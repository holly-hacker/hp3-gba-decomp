#include "types.h"
#include "color.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "modes.h"
#include "particles.h"
#include "buckbeak_minigame.h"
#include "menu/main_menu.h"
#include "mem.h"
#include "gen/graphics/menus.h"
#include "text_actor.h"

void InitializeBuckbeakMinigame(void)
{
    g_pBuckbeakMinigame = AllocZeroed(sizeof(BuckbeakMinigameState));
    ClearObjPaletteSlots();
    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    ClearBuckbeakMinigameRings();
    PlayMusicModule(0x30);
    g_pBuckbeakMinigame->dwScore = 0;
    ResetBuckbeakMinigame();
    SetUpBuckbeakMinigameScene();
    g_GameModeStackContext.dwModeState = BuckbeakMinigameStateFlying;
    g_apTextActors[BuckbeakMinigameTextResume] = NULL;
    g_apTextActors[BuckbeakMinigameTextReplay] = NULL;
    g_apTextActors[BuckbeakMinigameTextExit] = NULL;
    g_pBuckbeakMinigame->pCursor = NULL;
    DrawBuckbeakMinigameScore();
    DrawBuckbeakMinigameTime();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
