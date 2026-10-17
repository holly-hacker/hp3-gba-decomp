#include "types.h"
#include "char_block.h"
#include "graphics/display.h"
#include "modes.h"
#include "buckbeak_minigame.h"
#include "cursor.h"
#include "text_actor.h"
#include "main.h"

// Removes the results menu and sets the rings spinning again.
void CloseBuckbeakMinigameResultsMenu(void)
{
    s32 i;
    s32 j;

    ReleaseBuckbeakMinigameActor(&g_apTextActors[BuckbeakMinigameTextReplay]);
    ReleaseBuckbeakMinigameActor(&g_apTextActors[BuckbeakMinigameTextResume]);
    ReleaseBuckbeakMinigameActor(&g_apTextActors[BuckbeakMinigameTextExit]);
    g_GameModeStackContext.dwModeState = BuckbeakMinigameStateFlying;
    ReleaseMenuCursor(g_pBuckbeakMinigame->pCursor);
    FreeAllParticleEmitters();
    FreeAllParticles();
    g_dwGameModeFlags &= ~8;
    g_pBuckbeakMinigame->pBuckbeak->dwFlags |= ActorFlagHasAnimation;

    for (i = 0; i <= 8; i++)
    for (j = 0; j < 3; j++)
        SetActorOrbitAngleVels(g_pBuckbeakMinigame->aRings[i].apParts[j], 0x100, -0x100);

    ResumeBgTileAnimations();
}
