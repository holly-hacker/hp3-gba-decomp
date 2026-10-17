#include "types.h"
#include "char_block.h"
#include "graphics/display.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "text.h"
#include "buckbeak_minigame.h"
#include "cursor.h"
#include "text_actor.h"

// Opens the results menu: Resume Game (only while there is time), Replay and Exit Game.
void InitializeBuckbeakMinigameResultsMenu(void)
{
    const u8 *pText;
    s32 i;
    s32 j;

    g_GameModeStackContext.dwModeState = BuckbeakMinigameStateResults;

    if (g_pBuckbeakMinigame->dwTimeLeft > 0)
        g_pBuckbeakMinigame->dwMenuSelection = 0;
    else
        g_pBuckbeakMinigame->dwMenuSelection = 1;

    if (g_pBuckbeakMinigame->pCursor != NULL)
        ReleaseMenuCursor(g_pBuckbeakMinigame->pCursor);

    g_pBuckbeakMinigame->pCursor = SpawnMenuCursorActor(4);
    g_pBuckbeakMinigame->pCursor->pfnTick = MoveBuckbeakMinigameMenuCursor;
    g_pBuckbeakMinigame->pBuckbeak->dwFlags &= ~ActorFlagHasAnimation;
    SetActorPosition(g_pBuckbeakMinigame->pCursor, 0x78, g_pBuckbeakMinigame->dwMenuSelection * 16 + 0x48);

    if (g_pBuckbeakMinigame->dwTimeLeft > 0 && g_apTextActors[BuckbeakMinigameTextResume] == NULL)
    {
        pText = GetDialogText(0xA58);  // "Resume Game"
        SpawnTextActor(&pText, BuckbeakMinigameTextResume);
        SetTextActorCenterPosition_candidate(g_apTextActors[BuckbeakMinigameTextResume], 0x78, 0x40);
        g_apTextActors[BuckbeakMinigameTextResume]->oam.priority = 0;
    }

    if (g_apTextActors[BuckbeakMinigameTextReplay] == NULL)
    {
        pText = GetDialogText(0xA59);  // "Replay"
        SpawnTextActor(&pText, BuckbeakMinigameTextReplay);
        SetTextActorCenterPosition_candidate(g_apTextActors[BuckbeakMinigameTextReplay], 0x78, 0x50);
        g_apTextActors[BuckbeakMinigameTextReplay]->oam.priority = 0;
    }

    if (g_apTextActors[BuckbeakMinigameTextExit] == NULL)
    {
        pText = GetDialogText(0xA5A);  // "Exit Game"
        SpawnTextActor(&pText, BuckbeakMinigameTextExit);
        SetTextActorCenterPosition_candidate(g_apTextActors[BuckbeakMinigameTextExit], 0x78, 0x60);
        g_apTextActors[BuckbeakMinigameTextExit]->oam.priority = 0;
    }

    // Holds the rings still while the menu is open.
    for (i = 0; i <= 8; i++)
    for (j = 0; j < 3; j++)
        SetActorOrbitAngleVels(g_pBuckbeakMinigame->aRings[i].apParts[j], 0, 0);

    PauseBgTileAnimations();
}
