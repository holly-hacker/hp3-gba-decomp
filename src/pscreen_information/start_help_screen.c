#include "background.h"
#include "color.h"
#include "font.h"
#include "default_menu.h"
#include "pause_menu.h"
#include "screen_transitions.h"
#include "pscreen_information.h"
#include "gen/graphics/menus.h"

void StartHelpScreen(const u32 *pPageTable, s32 bStandalone)
{
    g_HelpState.bStandalone = bStandalone;
    if (bStandalone)
        BeginPauseMenuScreen(0);

    g_HelpState.bPageDepth = 0;
    g_HelpState.pCursor = NULL;
    g_HelpState.bSelectedEntry = 0;
    g_HelpState.dwSpriteCount = 0;
    ClearHelpScreen();
    ReserveObjPaletteSlot(0);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);

    if (!g_HelpState.bStandalone)
    {
        g_GameModeStackContext.dwModeSubState = 16;
        SetAlphaBlendTargets(0x14, 1);
        SetAlphaBlendCoefficients(16 - g_GameModeStackContext.dwModeSubState,
                                  g_GameModeStackContext.dwModeSubState);
    }

    SpawnHelpScreenTitle();
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    RunHelpScript(pPageTable);

    if (g_HelpState.bStandalone)
    {
        SetPaletteFadeParams(0, 8);
        PlayScreenTransitionInByIndex(0x3F, 2);
        SetPaletteFadeParams(0, 8);
        SetAlphaBlendTargets(4, 1);
        SetAlphaBlendCoefficients(16, 0);
        g_GameModeStackContext.dwModeState = HelpScreenStateBrowse;
    }
    else
    {
        g_GameModeStackContext.dwModeState = HelpScreenStateFadeIn;
    }

    g_HelpState.dwPaletteEffect = StartPaletteEffectWithFrameCount(
        6, 3, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette), 2);
}
