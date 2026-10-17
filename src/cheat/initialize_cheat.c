#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "combat_menu.h"
#include "hw/bios.h"
#include "cheat.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "actor.h"
#include "overworld/room.h"
#include "game/save.h"
#include "font.h"
#include "gen/graphics/menus.h"

void InitializeCheat(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Actor *pActor;
    u32 i;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCheatBg0Control);
    bgCtrl1 = g_dwCheatBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(7, 0, -1);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);

    g_CheatState.dwSelection = 0;
    pActor = SpawnActor(10, 0x78, 0x2D, (const ObjPalette *)gDebugMenuCursorPalette);
    g_CheatState.pCursorActor = pActor;
    pActor->dwFlags |= ActorFlagHasSpriteCells;
    SetActorAnimData(pActor, &g_CheatAnimFrames, (void *)g_CheatAnimData, 0);

    g_GameModeStackContext.dwModeState = 0;
    DrawCheatEntries();
    ResetCheatPartyFromArgs();
    g_dwOverworldMonstersDisabled = 0;

    for (i = 0; i < 3; i++)
        InitCharacterSpells_candidate(i, &g_aPartyMasterStats[i].wHp);

    PlayScreenTransitionInByIndex(0x3F, 2);
}
