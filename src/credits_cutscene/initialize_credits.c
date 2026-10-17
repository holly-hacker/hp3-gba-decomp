#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "modes.h"
#include "credits_cutscene.h"
#include "font.h"
#include "screen_transitions.h"

// Credits mode's pInitFn: sets up the credits BG layers, then starts the text scroll.
void InitializeCredits(void)
{
    u32 cutsceneIndex;
    u32 bgControl1;

    cutsceneIndex = g_GameModeStackContext.dwCurrentGameMode - Credits;
    ResetDisplayState(0);
    SetBgControl(0, g_dwLinearCutsceneBg0Control);
    bgControl1 = g_dwLinearCutsceneBg1Control;
    SetBgControl(1, bgControl1);
    FillBgTilemap(1, 0, 0);
    LoadBgGraphic(0, g_aLinearCutsceneTable[cutsceneIndex].pGraphic, 0, 0, 0, 0);
    SetTextTargetFromBgControl(bgControl1);
    SelectTextFont(4, 0, 0);
    SetBgScrollFixed(1, 0, 0);
    SetBgScrollStep(1, 0, 0x18000);
    g_dwCreditsScrollRow = 0xFF;
    g_dwCreditsLine = 0;
    g_dwCreditsTileCursor = 1;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
