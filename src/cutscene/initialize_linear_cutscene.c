#include "types.h"
#include "graphics/display.h"
#include "modes.h"
#include "cutscene.h"
#include "cursor.h"
#include "screen_transitions.h"

void InitializeLinearCutscene(void)
{
    u32 cutsceneIndex;

    cutsceneIndex = g_GameModeStackContext.dwCurrentGameMode - Credits;
    g_dwLinearCutsceneIndex = cutsceneIndex;
    g_pLinearCutsceneActor = SpawnMenuCursorActor(0);
    SetUpLinearCutscene(cutsceneIndex);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
