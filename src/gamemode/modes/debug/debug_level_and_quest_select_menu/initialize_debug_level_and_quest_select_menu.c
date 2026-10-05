#include "types.h"
#include "hw/bios.h"
#include "menu/debug_menu.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "graphics/object.h"
#include "overworld/room.h"
#include "graphics/text.h"
#include "gen/graphics/menus.h"

void InitializeDebugLevelAndQuestSelectMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Object *pObject;
    u32 args;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugLevelAndQuestBg0Control);
    bgCtrl1 = g_dwDebugLevelAndQuestBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(5, 0, -1);
    SetTextLineHeight(GetTextLineHeight() + 5);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugLevelAndQuestSelectState.dwRow = 0;
    g_DebugLevelAndQuestSelectState.adwValue[0] = 0;
    g_DebugLevelAndQuestSelectState.adwValue[1] = 0;
    g_DebugLevelAndQuestSelectState.adwValue[2] = 0;
    pObject = SpawnObject(10, 0x9C, 0x3A, (const ObjPalette *)gDebugMenuCursorPalette);
    g_DebugLevelAndQuestSelectState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, (void *)g_DebugLevelAndQuestAnimFrames, (void *)g_DebugLevelAndQuestAnimData, 0);

    args = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_DebugLevelAndQuestSelectState.adwValue[0] = (u8)(args >> 16);
    g_DebugLevelAndQuestSelectState.adwValue[1] = (u8)(args >> 8);
    g_DebugLevelAndQuestSelectState.adwValue[2] = (u8)args;
    g_DebugLevelAndQuestSelectState.adwValue[3] = args >> 24;
    g_GameModeStackContext.dwModeState = 0;
    sub_0800AD94();

    PlayScreenTransitionInByIndex(0x3F, 2);
}
