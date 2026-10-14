#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "cheat_wizard_cards.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "overworld/room.h"
#include "font.h"
#include "minigame/wizard_cracker_pop_it.h"

void InitializeCheatWizardCards(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl2;
    const u8 *pGraphic;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCheatWizardCardsBg0Control);
    SetBgControl(1, g_dwCheatWizardCardsBg1Control);
    bgCtrl2 = g_dwCheatWizardCardsBg2Control;
    SetBgControl(2, bgCtrl2);
    SetTextTargetFromBgControl(bgCtrl2);
    LoadBgGraphic(0, gFolioCardFrameRed, 0, 0, 0, 0);
    pGraphic = gDebugMenuGraphic;
    LoadGraphicBlob(1, pGraphic, 0, 0, 0, 0);
    LoadEmbeddedPalette((u8 *)pGraphic, 0, 3);
    SetBgScrollFixed(0, 0xFFCA0000, 0xFFE20000);

    g_CheatWizardCardsState.dwSelection = 0;
    g_CheatWizardCardsState.pCardActor = 0;
    g_GameModeStackContext.dwModeState = 0;
    ShowCheatWizardCard();

    PlayScreenTransitionInByIndex(0x3F, 2);
}
