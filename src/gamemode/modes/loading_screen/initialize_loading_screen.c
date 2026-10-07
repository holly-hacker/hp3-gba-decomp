#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "gen/graphics/menus.h"
#include "graphics/display.h"
#include "graphics/scanline_effects.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "menu/loading_screen.h"
#include "menu/main_menu.h"
#include "menu/dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void InitializeLoadingScreen(void)
{
    s32 stageRow;
    s32 bgRow;

    if (g_bCurrentRoomId == 1)
        SetAlphaBlendTargets(0, 0);

    bios_CPUSet(BG_PLTT, g_awSavedBgPalette0, 0x10);
    g_LoadingScreenState.bSavedBg2Priority = REG_BG2CNT & 3;
    sub_08024BD4();
    bgRow = sub_0800C6D0();
    g_dwLoadingScreenBgRow = bgRow;

    REG_WININ = (REG_WININ & 0xFF00) | 0x14;
    REG_WINOUT = (REG_WINOUT & 0xFF00) | 0x3F;
    SetScreenWindowRect_candidate(0, 0, 0x400000, 0xF00000, 0x800000);

    g_LoadingScreenState.pBgTilemap =
        LoadBgGraphic(2, gMenuPanel001, 0x200, 0, 0, g_dwLoadingScreenBgRow);
    QueueScanlineEffectTable(g_aLoadingScreenScanlineEffects, 2);
    while (!IsScanlineEffectQueueIdle())
        ;
    StartScanlineEffects();
    sub_08030960(1);
    sub_08030960(2);

    for (stageRow = 0; ; stageRow++)
    {
        if (g_LoadingScreenTables.abStages[stageRow] == g_abQuestEventState[0])
        {
            g_LoadingScreenState.bStageRow = stageRow;
            break;
        }
    }

    g_LoadingScreenState.abOptionStage[0] = g_GameModeStackContext.dwCurrentGameModeArg1;
    g_LoadingScreenState.abOptionStage[1] = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_LoadingScreenState.abOptionStage[2] = g_GameModeStackContext.dwCurrentGameModeArg3;
    g_LoadingScreenState.pCursorObject = sub_0801D940(1);
    sub_0800C344();

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwCurrentGameModeArg3 = g_abQuestEventState[0];
    SetObjectActionState(g_pPlayerObject, 0x24);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_GameModeStackContext.dwModeTimer = 5;
    sub_0800C3FC();
    SetBgPriority(2, 0);
    g_LoadingScreenState.bInputDelay = 10;
}
