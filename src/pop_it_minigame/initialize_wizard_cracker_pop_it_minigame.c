#include "types.h"
#include "background.h"
#include "color.h"
#include "sound.h"
#include "modes.h"
#include "mem.h"
#include "font.h"
#include "pop_it_minigame.h"
#include "screen_transitions.h"
#include "gen/graphics/minigames/wizard_cracker.h"

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
    LoadGraphicBlob(0, gWizardCrackerPopItBg0Graphic, 1, 0, 0, 0);
    SetBgControl(1, g_dwWizardCrackerPopItBg1Control);
    LoadBgGraphic(1, gWizardCrackerPopItBg1Graphic, 1, 0, 0, 0);
    SetBgControl(2, g_dwWizardCrackerPopItBg2Control);
    LoadGraphicBlob(2, gWizardCrackerPopItBg2Graphic, 1, 0, 0, 0);
    bgControl = g_dwWizardCrackerPopItBg3Control;
    SetBgControl(3, bgControl);
    ClearBgTilemap(3);
    SetBgScrollStep(0, 0, 0);
    SetBgScrollStep(1, 0, 0);
    SetBgScrollStep(2, 0, 0);
    SetBgScrollStep(3, 0, 0);
    ClearObjPaletteSlots();
    SetTextTargetFromBgControl(bgControl);
    SelectTextFont(6, 0, -1);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);

    g_pWizardCrackerPopIt->pActor0 = NULL;
    g_pWizardCrackerPopIt->dwScore = 0;

    pEntry = g_aWizardCrackerPopItPalettes;
    for (i = 4; i >= 0; i--)
    {
        pPalette = (void *)pEntry->pPalette;
        slotB = pEntry->bSlotB;
        LoadObjPaletteColors(pPalette, slotB << 4, 0x10);
        slotA = pEntry->bSlotA;
        LoadObjPaletteColors(pPalette, slotA << 4, 0x10);
        ReserveObjPaletteSlot(slotB);
        ReserveObjPaletteSlot(slotA);
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
