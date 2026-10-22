#include "types.h"
#include "actor.h"
#include "background.h"
#include "char_block.h"
#include "color.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fx.h"
#include "combat_fx_script.h"
#include "commands.h"
#include "gen/graphics/battle.h"
#include "hw/io_regs.h"
#include "map.h"
#include "mem.h"
#include "overworld/room.h"
#include "screen_transitions.h"

// The battle screen's VBlank callback: commits sprite tiles and BG animations, scrolls BG0
// and BG1, restores BG priorities after an effect, redraws the wall band, and applies a
// queued battle-message icon palette and BG load.
void HandleBattleVBlank(void)
{
    const u8 *pWall;

    CommitQueuedActorTileUpdates();
    CommitBgTileAnimations();
    REG_BGVOFS(1) = 264 - g_pFightState->bWallEndLine;
    REG_BGVOFS(0) = 0;
    REG_BGHOFS(1) = g_BgState.aLayers[1].scroll.x >> 16;
    REG_BGHOFS(0) = g_BgState.aLayers[0].scroll.x >> 16;

    if (g_effectStaging.dwBgPrioritiesPending) {
        SetBgPriority(0, g_effectStaging.bBg0Priority);
        SetBgPriority(1, g_effectStaging.bBg1Priority);
        g_effectStaging.dwBgPrioritiesPending = 0;
    } else {
        SetBgPriority(1, 1);
    }

    UploadPaletteShadows();

    if (g_abQuestEventState[QUEST_ALT_PRESENTATION]
        && IS_HOGWARTS_GROUNDS_ROOM(g_bCurrentRoomId))
        pWall = gBattleAltWall;
    else
        pWall = g_aBattleBackgroundPairs[g_bCurrentRoomId].pWall;
    CopyBgTilemapRect(1, GetGraphicBlobTilemap(1, pWall), 0x180, 0, 0, 0, 0, 23, 32, 8);
    CommitAlphaBlendCoefficients();

    if (g_StatsPortraitPaletteLoad.bBank != 0xFF
        && --g_StatsPortraitPaletteLoad.bCountdown == 0xFF) {
        CopyMemory(&g_pFightState->awPalette[g_StatsPortraitPaletteLoad.bBank * 16],
                   g_StatsPortraitPaletteLoad.pPalette, 0x80);
        g_StatsPortraitPaletteLoad.bBank |= 0xFF;
    }

    FlushQueuedBattleDma();
}
