#include "types.h"
#include "graphics/display.h"
#include "minigame/wizard_cracker_pop_it.h"
#include "graphics/text.h"
#include "game/game_modes.h"
#include "menu/folio_universitas.h"
#include "gen/graphics/cutscenes.h"
#include "gen/graphics/menus.h"

extern void DrawFolioCardDetailText(void);

void InitializeFolioCardDetailScreen(void)
{
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwFolioCardDetailBg3Control);
    SetBgControl(2, g_dwFolioCardDetailBg2Control);
    SetBgControl(1, g_dwFolioCardDetailBg1Control);
    ClearBgTilemap(1);
    ClearBgTilemap(2);

    switch (g_aFolioCardAssets[g_GameModeStackContext.dwCurrentGameModeArg2].dwFrame)
    {
    case FolioCardFrameBlue:
        LoadBgGraphic(2, gFolioCardFrameBlue, 1, 0, 14, 3);
        break;
    case FolioCardFramePurple:
        LoadBgGraphic(2, gFolioCardFramePurple, 1, 0, 14, 3);
        break;
    case FolioCardFrameRed:
        LoadBgGraphic(2, gFolioCardFrameRed, 1, 0, 14, 3);
        break;
    }

    sub_080077C8(3, gFolioCardDetailBg3Graphic, 1, 0, 0, 0);
    LoadEmbeddedPalette_candidate((u8 *)gFolioCardDetailBg3Graphic, 0, 3);
    SetTextTargetFromBgControl(g_dwFolioCardDetailBg1Control);
    DrawFolioCardDetailText();
    SpawnFolioCardObject(g_GameModeStackContext.dwCurrentGameModeArg2, 0x73, 0x18);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
