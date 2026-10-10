#include "types.h"
#include "math.h"
#include "game/game_modes.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "gen/graphics/menus.h"
#include "graphics/display.h"
#include "graphics/text.h"
#include "menu/folio_universitas.h"
#include "graphics/display.h"

void InitializeFolioUniversitas(void)
{
    u32 textBgControl;

    g_GameModeStackContext.dwModeState = 0;
    g_FolioUniversitasState.dwCategory = iwramDivideSignedRemainder(
        g_GameModeStackContext.dwCurrentGameModeArg2, 10, (s32 *)&g_FolioUniversitasState.dwSlot);

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwFolioUniversitasBg3Control);
    LoadBgGraphic(3, gFolioUniversitasBg3Graphic, 1, 0, 0, 0);
    textBgControl = g_dwFolioUniversitasBg1Control;
    SetBgControl(1, textBgControl);
    ClearBgTilemap(1);
    SetBgControl(0, g_dwFolioUniversitasBg0Control);
    g_FolioUniversitasState.pGridTilemap = LoadBgGraphic(0, gFolioUniversitasBg0Graphic, 1, 0, 0, 0);
    sub_0800D57C(0xB6, 5, 0xA, 0, 0x19, (const u8 *)gFolioUniversitasBg3Graphic + 0x162, 4);

    DrawFolioUniversitasCardSlots();
    SetTextTargetFromBgControl(textBgControl);
    DrawFolioUniversitasHeadings();
    DrawFolioUniversitasNames(1);
    ClearResourceCacheSlots();
    SpawnFolioUniversitasButtonPrompts();
    SpawnFolioUniversitasCursor();
    DrawFolioUniversitasButtonHints();
    UpdateFolioComboSlots();
    HighlightFolioComboSlot();

    sub_0800D57C(g_FolioUniversitasState.pCursor->oam.paletteNum * 16, 0x10, 0xF, 0, 0x1D,
                 GRAPHIC_BLOB_PALETTE_COLORS(gMenuCursor001), 6);
    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(8, 8);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
