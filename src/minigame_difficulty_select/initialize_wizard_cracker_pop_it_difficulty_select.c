#include "types.h"
#include "sound.h"
#include "modes.h"
#include "minigame_difficulty_select.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "cursor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void InitializeWizardCrackerPopItDifficultySelect(void)
{
    s32 i;

    SetAlphaBlendTargets(0, 0);
    InitializeMenuScreen(g_dwSelectedMinigame + 0xA4A, 4, 1, gMenuScreenGraphic, 0, 0);  // minigame name
    g_pMenuCursorActor->oam.hFlip = 1;
    SetMenuCursorPosition(g_pMenuCursorActor, 0x60, 0x30);

    if (g_PrevGameModeStackContext.dwCurrentGameMode != MinigameMenu)
        PlayMusicModule(0x21);

    g_GameModeStackContext.dwModeScratchB = 0;
    for (i = 0; i <= MINIGAME_ERASE_SCORES_ROW; i++)
        DrawMinigameDifficultyRow(i, i == 0 ? 6 : 1);

    DrawMinigameDifficultyHighScore(g_GameModeStackContext.dwModeScratchB);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
