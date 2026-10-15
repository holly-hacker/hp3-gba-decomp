#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "gen/graphics/menus.h"
#include "graphics/display.h"
#include "graphics/scanline_effects.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "menu/choose_character.h"
#include "menu/main_menu.h"
#include "dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "cursor.h"

void InitializeChooseCharacter(void)
{
    s32 stageRow;
    s32 bgRow;

    if (g_bCurrentRoomId == 1)
        SetAlphaBlendTargets(0, 0);

    bios_CPUSet(BG_PLTT, g_awSavedBgPalette0, 0x10);
    g_ChooseCharacterState.bSavedBg2Priority = REG_BG2CNT & 3;
    sub_08024BD4();
    bgRow = GetChooseCharacterPanelBgRow();
    g_dwChooseCharacterBgRow = bgRow;

    REG_WININ = (REG_WININ & 0xFF00) | 0x14;
    REG_WINOUT = (REG_WINOUT & 0xFF00) | 0x3F;
    SetScreenWindowRect_candidate(0, 0, 0x400000, 0xF00000, 0x800000);

    g_ChooseCharacterState.pBgTilemap =
        LoadBgGraphic(2, gMenuPanel001, 0x200, 0, 0, g_dwChooseCharacterBgRow);
    QueueScanlineEffectTable(g_aChooseCharacterScanlineEffects, 2);
    while (!IsScanlineEffectQueueIdle())
        ;
    StartScanlineEffects();
    UnreserveObjPaletteSlot(1);
    UnreserveObjPaletteSlot(2);

    for (stageRow = 0; ; stageRow++)
    {
        if (g_abChooseCharacterStages[stageRow] == g_abQuestEventState[0])
        {
            g_ChooseCharacterState.bStageRow = stageRow;
            break;
        }
    }

    g_ChooseCharacterState.abOptionStage[0] = g_GameModeStackContext.dwCurrentGameModeArg1;
    g_ChooseCharacterState.abOptionStage[1] = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_ChooseCharacterState.abOptionStage[2] = g_GameModeStackContext.dwCurrentGameModeArg3;
    g_ChooseCharacterState.pCursorActor = SpawnMenuCursorActor(1);
    SpawnChooseCharacterOptionActors();

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwCurrentGameModeArg3 = g_abQuestEventState[0];
    SetActorActionState(g_pPlayerActor, 0x24);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_GameModeStackContext.dwModeTimer = 5;
    DrawChooseCharacterSelection();
    SetBgPriority(2, 0);
    g_ChooseCharacterState.bInputDelay = 10;
}
