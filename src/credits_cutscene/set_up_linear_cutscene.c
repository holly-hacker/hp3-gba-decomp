#include "types.h"
#include "background.h"
#include "credits_cutscene.h"
#include "font.h"
#include "text.h"

#ifdef VERSION_JP
#define CUTSCENE_TEXT_FONT 10
#else
#define CUTSCENE_TEXT_FONT 7
#endif

// Sets up the BG layers and font for cutscene `cutsceneIndex`, then draws its
// first page, showing the cutscene actor while more text remains.
void SetUpLinearCutscene(u32 cutsceneIndex)
{
    u32 bgControl1;
    const u8 **ppText;

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwLinearCutsceneBg0Control);
    bgControl1 = g_dwLinearCutsceneBg1Control;
    SetBgControl(1, bgControl1);
    FillBgTilemap(1, 0, 0);
    LoadBgGraphic(0, g_aLinearCutsceneTable[cutsceneIndex].pGraphic, 0, 0, 0, 0);
    SetTextTargetFromBgControl(bgControl1);
    SelectTextFont(CUTSCENE_TEXT_FONT, 0, -1);
    ppText = &g_pLinearCutsceneText;
    *ppText = GetDialogText(g_aLinearCutsceneTable[cutsceneIndex].dwTextId);
    ClearBgTilemap(1);
    DrawTextLines(1, 2, 0x7A, 0xE6, 0x24, ppText, 0);

    if (**ppText != 0)
        g_pLinearCutsceneActor->dwFlags |= ActorFlagVisible;
    else
        g_pLinearCutsceneActor->dwFlags &= ~ActorFlagVisible;
}
