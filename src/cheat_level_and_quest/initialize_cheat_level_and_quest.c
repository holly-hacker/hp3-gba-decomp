#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "cheat_level_and_quest.h"
#include "modes.h"
#include "hw/io_regs.h"
#include "actor.h"
#include "font.h"
#include "gen/graphics/menus.h"
#include "screen_transitions.h"
#include "video.h"

void InitializeCheatLevelAndQuest(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Actor *pActor;
    u32 args;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCheatLevelAndQuestBg0Control);
    bgCtrl1 = g_dwCheatLevelAndQuestBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(5, 0, -1);
    SetTextLineHeight(GetTextLineHeight() + 5);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);

    g_CheatLevelAndQuestState.dwRow = 0;
    g_CheatLevelAndQuestState.adwValue[0] = 0;
    g_CheatLevelAndQuestState.adwValue[1] = 0;
    g_CheatLevelAndQuestState.adwValue[2] = 0;
    pActor = SpawnActor(10, 0x9C, 0x3A, (const ObjPalette *)gDebugMenuCursorPalette);
    g_CheatLevelAndQuestState.pCursorActor = pActor;
    pActor->dwFlags |= ActorFlagHasSpriteCells;
    SetActorAnimData(pActor, &g_CheatLevelAndQuestAnimFrames, (void *)g_CheatLevelAndQuestAnimData, 0);

    args = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_CheatLevelAndQuestState.adwValue[0] = (u8)(args >> 16);
    g_CheatLevelAndQuestState.adwValue[1] = (u8)(args >> 8);
    g_CheatLevelAndQuestState.adwValue[2] = (u8)args;
    g_CheatLevelAndQuestState.adwValue[3] = args >> 24;
    g_GameModeStackContext.dwModeState = 0;
    DrawCheatLevelAndQuestRows();

    PlayScreenTransitionInByIndex(0x3F, 2);
}
