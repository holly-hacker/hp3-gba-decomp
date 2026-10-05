#include "types.h"
#include "hw/bios.h"
#include "menu/debug_menu.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "hw/io_regs.h"
#include "graphics/object.h"
#include "overworld/room.h"
#include "graphics/text.h"
#include "gen/graphics/menus.h"

void InitializeDebugMapSelectMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Object *pObject;

    StopScanlineEffects();
    ClearResourceCacheSlots();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugMapSelectBg0Control);
    bgCtrl1 = g_dwDebugMapSelectBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(7, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugMapSelectState.dwCursorRow = 0;
    g_DebugMapSelectState.nScrollY = 0;
    pObject = SpawnObject(0x17, 0x78, 0xB, (const ObjPalette *)gDebugMenuCursorPalette);
    g_DebugMapSelectState.pCursorObject = pObject;
    SetObjectAnimData(pObject, (void *)g_DebugMapSelectAnimFrames, (void *)g_DebugMapSelectAnimData, 0);

    sub_0800B120();
    g_GameModeStackContext.dwModeTimer = 2;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
