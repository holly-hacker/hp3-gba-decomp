#include "types.h"
#include "background.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "overworld/room.h"

void ResetDisplayState(u16 mode)
{
    REG_DISPCNT = mode | 0x40;
    g_BgState.aLayers[2].wZoom = 0x100;
    g_BgState.aLayers[3].wZoom = 0x100;
    if (!(g_dwGameModeFlags & 0x80000))
        ResetCameraPosition();
    ResetBgLayers();
}
