#include "types.h"
#include "background.h"
#include "font.h"
#include "cheat_wizard_cards.h"
#include "menu/folio_universitas.h"
#include "gen/graphics/menus.h"

void ShowCheatWizardCard(void)
{
    const u8 *name;

    if (g_CheatWizardCardsState.pCardActor != NULL)
        FreeActor(g_CheatWizardCardsState.pCardActor);

    g_CheatWizardCardsState.pCardActor =
        SpawnFolioCardActor(g_CheatWizardCardsState.dwSelection, 0x37, 0x1F);

    switch (g_aFolioCardAssets[g_CheatWizardCardsState.dwSelection].dwFrame)
    {
    case FolioCardFrameBlue:
        LoadGraphicBlob(0, gFolioCardFrameBlue, 0, 0, 0, 0);
        LoadEmbeddedPaletteFromRow(gFolioCardFrameBlue, 3);
        SetBgScrollFixed(0, 0xFFCA0000, 0xFFE20000);
        break;
    case FolioCardFramePurple:
        LoadGraphicBlob(0, gFolioCardFramePurple, 0, 0, 0, 0);
        LoadEmbeddedPaletteFromRow(gFolioCardFramePurple, 3);
        SetBgScrollFixed(0, 0xFFCA0000, 0xFFE20000);
        break;
    case FolioCardFrameRed:
        LoadGraphicBlob(0, gFolioCardFrameRed, 0, 0, 0, 0);
        LoadEmbeddedPaletteFromRow(gFolioCardFrameRed, 3);
        SetBgScrollFixed(0, 0xFFCA0000, 0xFFE20000);
        break;
    case 3:
        LoadGraphicBlob(0, gFolioCardFrameSilver, 1, 0, 0, 0);
        LoadEmbeddedPaletteFromRow(gFolioCardFrameSilver, 3);
        SetBgScrollFixed(0, 0xFFCA0000, 0xFFE20000);
        break;
    }

    ClearBgTilemap(2);
    SelectTextFont(9, 0, -1);
    name = sFamousWizardCardNames[g_CheatWizardCardsState.dwSelection];
    PrintTextBox(0x1A0, 0x78, 0x10, 0xE0, name, 1);
}
