#include "types.h"
#include "combo_info.h"
#include "modes.h"
#include "gen/graphics/cutscenes.h"
#include "actor.h"
#include "font.h"
#include "text.h"
#include "pscreen_folio_universitas.h"
#include "pause_menu.h"
#include "default_menu.h"
#include "screen_transitions.h"

#ifdef VERSION_JP
#define DESCRIPTION_Y 0x6A
#else
#define DESCRIPTION_Y 0x68
#endif

// Shows the three cards of a combo with the combo's name and description. Cards the player has
// never collected are shown as the dimmed face-down card.
void InitializeCardComboDescription(void)
{
    u32 firstCard = GetFolioUniversitasSelectedCombo();
    u32 tileCursor;
    s32 slot;
    Actor *pActor;
    u8 *pText;

    InitializeMenuScreen(0x40C, 9, 1, gCardComboDescriptionPanel, 5, 5);  // "Card Combo"
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(1, 0xD, -1);
    pText = GetDialogText(g_GameModeStackContext.dwCurrentGameModeArg3 + 0x478);
    tileCursor = DrawString(0x61, 0x28, 0x60, pText);
    SelectTextFont(1, 0, -1);
    pText = GetDialogText(g_GameModeStackContext.dwCurrentGameModeArg3 + 0x488);
    PrintTextBox(tileCursor, 0x28, DESCRIPTION_Y, 0xA0, pText, 0);

    if (firstCard <= 0x31)
    {
        for (slot = 0; slot < 3; slot++)
        {
            if (IsFolioUniversitasCardSeen(firstCard + slot))
            {
                pActor = SpawnActor(0, 0x40 + slot * 0x28, 0x30,
                                      (const ObjPalette *)g_aFolioCardThumbnails[firstCard + slot].pPalette);
                SetActorAssetRecord(pActor, &g_aFolioCardThumbnails[firstCard + slot]);
            }
            else
            {
                pActor = SpawnActor(0, 0x40 + slot * 0x28, 0x30,
                                      (const ObjPalette *)g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT].pPalette);
                SetActorAssetRecord(pActor, &g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT]);
                pActor->oam.objMode = 1;
            }
        }
    }
    else
    {
        if (IsFolioUniversitasCardSeen(firstCard))
        {
            pActor = SpawnActor(0, 0x68, 0x30, (const ObjPalette *)g_aFolioCardThumbnails[firstCard].pPalette);
            SetActorAssetRecord(pActor, &g_aFolioCardThumbnails[firstCard]);
        }
        else
        {
            pActor = SpawnActor(0, 0x68, 0x30,
                                  (const ObjPalette *)g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT].pPalette);
            SetActorAssetRecord(pActor, &g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT]);
            pActor->oam.objMode = 1;
        }
    }

    PlayScreenTransitionInByIndex(0x3F, 2);
}
