#include "types.h"
#include "battle.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "object.h"
#include "room.h"
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
    ResetDisplayState_candidate(0);
    SetDispcntFlag(0x1000);
    SetBgControl_candidate(0, g_dwDebugMenuMainBg0Control);
    bgCtrl1 = g_dwDebugMenuMainBg1Control;
    SetBgControl_candidate(1, bgCtrl1);
    LoadBgGraphic_candidate(0, g_DebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap_candidate(1);
    SetTextTargetFromBgControl_candidate(bgCtrl1);
    SelectTextFont_candidate(7, 0, -1);
    sub_08007B88(0, 0, 0);
    sub_08007B88(1, 0, 0);

    g_DebugMenuMainState.dwSelection = 0;
    pObject = SpawnObject(10, 0x78, 0x2D, g_DebugMenuCursorSpawnData);
    g_DebugMenuMainState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, (void *)g_DebugMenuMainAnimFrames, (void *)g_DebugMenuMainAnimData, 0);

    g_GameModeStackContext.dwModeState_candidate = 0;
    DrawDebugMenuMainEntries_candidate();
    ResetDebugPartyFromArgs_candidate();
    g_dwOverworldMonstersDisabled = 0;

    for (i = 0; i < 3; i++)
        InitCharacterSpells_candidate(i, &g_aPartyMasterStats[i].wHp);

    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
}
