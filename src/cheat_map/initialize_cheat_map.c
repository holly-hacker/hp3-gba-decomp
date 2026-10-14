#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "cheat_map.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "hw/io_regs.h"
#include "actor.h"
#include "overworld/room.h"
#include "font.h"
#include "gen/graphics/menus.h"

void InitializeCheatMap(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Actor *pActor;

    StopScanlineEffects();
    ClearObjPaletteSlots();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCheatMapBg0Control);
    bgCtrl1 = g_dwCheatMapBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(7, 0, -1);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);

    g_CheatMapState.dwCursorRow = 0;
    g_CheatMapState.nScrollY = 0;
    pActor = SpawnActor(0x17, 0x78, 0xB, (const ObjPalette *)gDebugMenuCursorPalette);
    g_CheatMapState.pCursorActor = pActor;
    SetActorAnimData(pActor, &g_CheatMapAnimFrames, (void *)g_CheatMapAnimData, 0);

    sub_0800B120();
    g_GameModeStackContext.dwModeTimer = 2;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
