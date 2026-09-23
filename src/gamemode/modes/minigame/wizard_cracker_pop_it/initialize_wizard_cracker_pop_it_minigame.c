#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "graphics.h"
#include "mem.h"
#include "text.h"
#include "wizard_cracker_pop_it.h"

void InitializeWizardCrackerPopItMinigame(void)
{
    const WizardCrackerPopItPaletteEntry *pEntry;
    void *pPalette;
    u32 bgControl;
    u32 slotA;
    u32 slotB;
    s32 i;

    g_pWizardCrackerPopIt = AllocZeroed(sizeof(WizardCrackerPopItState));

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwWizardCrackerPopItBg0Control);
    sub_080077C8(0, g_WizardCrackerPopItBg0Graphic, 1, 0, 0, 0);
    SetBgControl(1, g_dwWizardCrackerPopItBg1Control);
    LoadBgGraphic(1, g_WizardCrackerPopItBg1Graphic, 1, 0, 0, 0);
    SetBgControl(2, g_dwWizardCrackerPopItBg2Control);
    sub_080077C8(2, g_WizardCrackerPopItBg2Graphic, 1, 0, 0, 0);
    bgControl = g_dwWizardCrackerPopItBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    sub_08007D14(0, 0, 0);
    sub_08007D14(1, 0, 0);
    sub_08007D14(2, 0, 0);
    sub_08007D14(3, 0, 0);
    ClearResourceCacheSlots();
    SetTextTargetFromBgControl(bgControl);
    SelectTextFont(6, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_pWizardCrackerPopIt->pObject0 = NULL;
    g_pWizardCrackerPopIt->dwScore = 0;

    pEntry = g_aWizardCrackerPopItPalettes;
    for (i = 4; i >= 0; i--)
    {
        pPalette = (void *)pEntry->pPalette;
        slotB = pEntry->bSlotB;
        sub_0800D254(pPalette, slotB << 4, 0x10);
        slotA = pEntry->bSlotA;
        sub_0800D254(pPalette, slotA << 4, 0x10);
        sub_0803094C(slotB);
        sub_0803094C(slotA);
        pEntry++;
    }

    sub_08032AA8();
    sub_08033D34();
    PlayMusicModule(0x16);
    g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
    g_GameModeStackContext.dwModeTimer = 8;
    PlayScreenTransitionInByIndex(0x3F, 2);
    SetAlphaBlendTargets(4, 2);
    g_pWizardCrackerPopIt->dwUnk1A8 = 0;
    g_pWizardCrackerPopIt->bUnk180 = 0;
}
