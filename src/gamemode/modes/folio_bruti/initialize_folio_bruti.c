#include "types.h"
#include "game/game_modes.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "gen/graphics/overworld.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "graphics/text.h"
#include "menu/folio_bruti.h"

void InitializeFolioBruti(void)
{
    s32 i;
    u32 monster;
    u32 textBgControl;

    g_FolioBrutiState.pMonster = NULL;
    g_FolioBrutiState.pCursor = NULL;
    for (i = 0; i < ARRAY_COUNT(g_FolioBrutiState.apSpellDots); i++)
        g_FolioBrutiState.apSpellDots[i] = NULL;
    g_FolioBrutiState.dwUnk0 = 0;

    // Coming from battle, start on the monster being fought.
    if (g_PrevGameModeStackContext.dwCurrentGameMode == Battle)
    {
        monster = g_GameModeStackContext.dwCurrentGameModeArg2;
        g_FolioBrutiState.dwColumn = monster % 9;
        g_FolioBrutiState.dwRow = monster / 9;
    }
    else
    {
        g_FolioBrutiState.dwColumn = 0;
        g_FolioBrutiState.dwRow = 0;
    }

    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(3, g_dwFolioBrutiBg3Control);
    g_FolioBrutiState.pGridTilemap = LoadBgGraphic(3, gFolioBrutiBg3Graphic, 1, 0, 0, 0);
    SetBgControl(2, g_dwFolioBrutiBg2Control);
    LoadBgGraphic(2, gFolioBrutiBg2Graphic, 0x1FA, 0, 0, 0);
    DrawFolioBrutiGrid();
    textBgControl = g_dwFolioBrutiBg1Control;
    SetBgControl(1, textBgControl);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(textBgControl);
    DrawFolioBrutiHeading();
    DrawFolioBrutiMonsterText();
    sub_0800D57C(0x3E, 2, 0xA, 0, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gFolioBrutiBg3Graphic) + 0x30, 4);

    g_FolioBrutiState.pCursor = SpawnObject(0, (g_FolioBrutiState.dwColumn + 3) * 8, (g_FolioBrutiState.dwRow + 3) * 8,
                                            (const ObjPalette *)gFolioBrutiSpellDotPalette);
    SetObjectAnimData(g_FolioBrutiState.pCursor, FOLIO_BRUTI_CURSOR_GFX, g_aFolioBrutiCursorAnim, 0);
    g_FolioBrutiState.pCursor->oam.priority = 1;

    SetAlphaBlendTargets(0, 0x1F);
    DrawFolioBrutiMonsterPanel();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
