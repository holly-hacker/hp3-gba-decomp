#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"
#include "menu/minigame_difficulty_select.h"
#include "gen/graphics/minigames/hippogriff.h"

void InitializeWizardCrackerPopItDifficultySelect(void)
{
    s32 i;

    SetAlphaBlendTargets(0, 0);
    InitializeMenuScreen(g_dwSelectedMinigame + 0xA4A, 4, 1, gMenuScreenGraphic, 0, 0);  // minigame name
    g_pMenuCursorObject->oam.hFlip = 1;
    sub_0801DCC4(g_pMenuCursorObject, 0x60, 0x30);

    if (g_PrevGameModeStackContext.dwCurrentGameMode != MinigameMenu)
        PlayMusicModule(0x21);

    g_GameModeStackContext.dwModeScratchB = 0;
    for (i = 0; i <= MINIGAME_ERASE_SCORES_ROW; i++)
        sub_0802CB80(i, i == 0 ? 6 : 1);

    sub_0802CC44(g_GameModeStackContext.dwModeScratchB);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
