#include "types.h"
#include "modes.h"
#include "background.h"
#include "hw/io_regs.h"
#include "scroll.h"
#include "main.h"

void ResetDisplayState(u16 mode)
{
    REG_DISPCNT = mode | 0x40;
    g_BgState.aLayers[2].wZoom = 0x100;
    g_BgState.aLayers[3].wZoom = 0x100;
    if (!(g_dwGameModeFlags & GameModeFlagUnk80000))
        ResetCameraPosition();
    ResetBgLayers();
}
