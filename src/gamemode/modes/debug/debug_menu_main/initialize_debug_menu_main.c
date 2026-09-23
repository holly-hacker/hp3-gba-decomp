#include "types.h"
#include "battle.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "object.h"
#include "room.h"
#include "save.h"
#include "text.h"

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
    LoadBgGraphic(0, g_DebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(7, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugMenuMainState.dwSelection = 0;
    pObject = SpawnObject(10, 0x78, 0x2D, g_DebugMenuCursorSpawnData);
    g_DebugMenuMainState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, (void *)g_DebugMenuMainAnimFrames, (void *)g_DebugMenuMainAnimData, 0);

    g_GameModeStackContext.dwModeState = 0;
    DrawDebugMenuMainEntries_candidate();
    ResetDebugPartyFromArgs_candidate();
    g_dwOverworldMonstersDisabled = 0;

    for (i = 0; i < 3; i++)
        InitCharacterSpells_candidate(i, &g_aPartyMasterStats[i].wHp);

    PlayScreenTransitionInByIndex(0x3F, 2);
}
