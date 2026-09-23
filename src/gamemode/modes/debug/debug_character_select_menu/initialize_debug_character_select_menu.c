#include "types.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "object.h"
#include "overworld.h"
#include "room.h"
#include "text.h"

void InitializeDebugCharacterSelectMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Object *pObject;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugCharacterSelectBg0Control);
    bgCtrl1 = g_dwDebugCharacterSelectBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, g_DebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(5, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugCharacterSelectState.dwRow = 0;
    g_DebugCharacterSelectState.adwCharacter[0] = 0;
    g_DebugCharacterSelectState.adwCharacter[1] = 0;
    g_DebugCharacterSelectState.adwCharacter[2] = 0;
    pObject = SpawnObject(10, 0x9C, 0x3A, g_DebugMenuCursorSpawnData);
    g_DebugCharacterSelectState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, (void *)g_DebugCharacterSelectAnimFrames, (void *)g_DebugCharacterSelectAnimData, 0);

    g_DebugCharacterSelectState.adwCharacter[0] = g_bPartyCharId0 == 0xFF ? 0 : g_bPartyCharId0 + 1;
    g_DebugCharacterSelectState.adwCharacter[1] = g_bPartyCharId1 == 0xFF ? 0 : g_bPartyCharId1 + 1;
    g_DebugCharacterSelectState.adwCharacter[2] = g_bPartyCharId2 == 0xFF ? 0 : g_bPartyCharId2 + 1;
    g_GameModeStackContext.dwModeState = 0;
    sub_0800B344();

    PlayScreenTransitionInByIndex(0x3F, 2);
}
