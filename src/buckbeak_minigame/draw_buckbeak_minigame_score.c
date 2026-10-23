#include "types.h"
#include "font.h"
#include "text.h"
#include "buckbeak_minigame.h"
#include "text_actor.h"

void DrawBuckbeakMinigameScore(void)
{
    const u8 *pText;

    ReleaseBuckbeakMinigameActor(&g_apTextActors[BuckbeakMinigameTextScore]);
    SetTextMacro1Number(g_pBuckbeakMinigame->dwScore);
    pText = GetDialogText(0xA5D);  // "Score: @1"
    SpawnTextActor(&pText, BuckbeakMinigameTextScore);

    // Centered once the time has run out, tucked into the corner while flying.
    if (g_pBuckbeakMinigame->dwTimeLeft == 0)
        SetTextActorCenterPosition(g_apTextActors[BuckbeakMinigameTextScore], 0x78, 0x28);
    else
        SnapActorPosition(g_apTextActors[BuckbeakMinigameTextScore], 0x60000, 0x900000);

    g_apTextActors[BuckbeakMinigameTextScore]->oam.priority = 0;
}
