#include "types.h"
#include "battle/battle.h"
#include "hw/bios.h"
#include "menu/debug_menu.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "graphics/object.h"
#include "overworld/room.h"
#include "game/save.h"
#include "graphics/text.h"
#include "gen/graphics/menus.h"

void InitializeDebugMenuMain(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Object *pObject;
    u32 i;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugMenuMainBg0Control);
    bgCtrl1 = g_dwDebugMenuMainBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(7, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugMenuMainState.dwSelection = 0;
    pObject = SpawnObject(10, 0x78, 0x2D, (const ObjPalette *)gDebugMenuCursorPalette);
    g_DebugMenuMainState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, &g_DebugMenuMainAnimFrames, (void *)g_DebugMenuMainAnimData, 0);

    g_GameModeStackContext.dwModeState = 0;
    DrawDebugMenuMainEntries_candidate();
    ResetDebugPartyFromArgs_candidate();
    g_dwOverworldMonstersDisabled = 0;

    for (i = 0; i < 3; i++)
        InitCharacterSpells_candidate(i, &g_aPartyMasterStats[i].wHp);

    PlayScreenTransitionInByIndex(0x3F, 2);
}
