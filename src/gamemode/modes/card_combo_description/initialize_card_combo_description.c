#include "types.h"
#include "game/game_modes.h"
#include "gen/graphics/cutscenes.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "graphics/text.h"
#include "menu/folio_universitas.h"
#include "menu/main_menu.h"
#include "menu/menu.h"

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
    Object *pObject;
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
                pObject = SpawnObject(0, 0x40 + slot * 0x28, 0x30,
                                      (const ObjPalette *)g_aFolioCardThumbnails[firstCard + slot].pPalette);
                SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[firstCard + slot]);
            }
            else
            {
                pObject = SpawnObject(0, 0x40 + slot * 0x28, 0x30,
                                      (const ObjPalette *)g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT].pPalette);
                SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT]);
                pObject->oam.objMode = 1;
            }
        }
    }
    else
    {
        if (IsFolioUniversitasCardSeen(firstCard))
        {
            pObject = SpawnObject(0, 0x68, 0x30, (const ObjPalette *)g_aFolioCardThumbnails[firstCard].pPalette);
            SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[firstCard]);
        }
        else
        {
            pObject = SpawnObject(0, 0x68, 0x30,
                                  (const ObjPalette *)g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT].pPalette);
            SetObjectAssetRecord(pObject, &g_aFolioCardThumbnails[FOLIO_UNIVERSITAS_CARD_COUNT]);
            pObject->oam.objMode = 1;
        }
    }

    PlayScreenTransitionInByIndex(0x3F, 2);
}
