#include "types.h"
#include "background.h"
#include "color.h"
#include "combat.h"
#include "combat_core.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "commands.h"
#include "font.h"
#include "gen/graphics/battle.h"
#include "gen/graphics/menus.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "map.h"
#include "mem.h"
#include "mode7.h"
#include "overworld/room.h"
#include "palette.h"
#include "particles.h"
#include "screen_transitions.h"
#include "video.h"
#include "vram.h"

// Sets up the battle screen: the perspective floor on BG2, the wall band and HUD panel on
// BG1, battle text on BG0, the HUD palette, floor camera and scanline effects. Rooms 8-15
// use a fixed alternate floor and wall while the quest's alternate presentation is on.
void InitBattleDisplay(void)
{
    const u8 *pFloor;
    const u8 *pWall;
    const u8 *pHud;

    g_dwPaletteRedirect = 0;
    g_dwScreenPaletteDarkened = 0;
    SetVBlankCallback(HandleBattleVBlank);
    InitObjTileAllocBitmaps(1);
    memset(VRAM_BASE, 0, 0x18000);

    if (g_abQuestEventState[QUEST_ALT_PRESENTATION]
        && IS_HOGWARTS_GROUNDS_ROOM(g_bCurrentRoomId))
        pFloor = gBattleAltFloor;
    else
        pFloor = g_aBattleBackgroundPairs[g_bCurrentRoomId].pFloor;
    InitFloorDisplay(pFloor, &g_dwBattleFloorBgControl, NULL, NULL, 20, 0);
    SetFloorHorizonLineAndSkyScroll(2, 0);

    SetBgControl(1, g_dwBattleBg1Control);
    SetBgControl(0, g_dwBattleBg0Control);
    SetDispcntFlag(0x1000);
    SetTextTargetFromBgControl(g_dwBattleBg0Control);
    g_pFightState->dwStatsTextTileCursor = 0x60;
    g_pFightState->dwTextTileCursor = 0xA0;
    SelectTextFont(1, 0, -1);

    pHud = gBattleHudPanel;
    CopyBgTilemapRect(1, LoadGraphicBlobTiles(1, pHud, 1), 1, 0, 0, 0, 0, 19, 30, 6);
    pHud += 2;  // the blob's embedded palette, after its two flag bytes
    CopyMemory(g_pFightState->awPalette, pHud, 0x100);

    if (g_abQuestEventState[QUEST_ALT_PRESENTATION]
        && IS_HOGWARTS_GROUNDS_ROOM(g_bCurrentRoomId))
        pWall = gBattleAltWall;
    else
        pWall = g_aBattleBackgroundPairs[g_bCurrentRoomId].pWall;
    CopyBgTilemapRect(1, LoadGraphicBlobTiles(1, pWall, 0x180), 0x180, 0, 0, 0, 0, 23, 32, 8);

    SetFloorCameraPositionAndHeading(120, 80, 0);
    SetFloorHorizonOffset(0);
    SetFloorCameraHeight(250);
    SetFloorForwardSpeed(0);
    g_FloorEffect.dwCameraBackoff = 100;
    UpdateFloorAffineTable();

    g_pFightState->bWallEndLine = 64;
    QueueBattleScanlineEffects();
    StartScanlineEffects();

    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 16);
    ReserveObjPaletteSlot(0);
    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(8, 8);
    LoadParticleGfx(0, 0, &g_BattleEffect001Asset);
}
