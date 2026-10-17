#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "game/game_modes.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "landmarks.h"
#include "mt19937.h"
#include "cursor.h"

void InitializeUnusedHogwartsMapScreen(void)
{
    u16 fillValue;
    u16 *pFillValue;

    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);

    g_pUnusedHogwartsMapCursor = SpawnMenuCursorActor(4);
    g_pUnusedHogwartsMapCursor->oam.hFlip = 1;

    SetBgControl(0, g_dwUnusedHogwartsMapBg0Control);
    SetBgControl(1, g_dwUnusedHogwartsMapBg1Control);
    SetBgControl(2, g_dwUnusedHogwartsMapBg2Control);
    SetBgControl(3, g_dwUnusedHogwartsMapBg3Control);
    SetBgScrollFixed(0, 0, 0);
    SetBgScrollFixed(1, 0, 0);
    SetBgScrollFixed(2, 0, 0);
    SetBgScrollFixed(3, 0, 0);

    LoadBgGraphic(0, gHippogriffLanguageMinigameBgs011, 1, 0, 0, 0);
    g_pUnusedHogwartsMapBg1Tilemap = LoadBgGraphic(1, gHippogriffLanguageMinigameBgs012, 0x181, 0, 0, 0);
    ClearBgTilemap(2);
    ClearBgTilemap(3);

    sub_080281AC();
    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    sub_08028240();
    sub_080282C4();
    Mt19937AutoSeed();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
