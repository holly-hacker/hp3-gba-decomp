#include "types.h"
#include "hw/io_regs.h"
#include "graphics/display.h"
#include "graphics/floor_effect.h"
#include "buckbeak_minigame.h"

// Runs at the horizon line: switches BG2 to the ground.
void BeginBuckbeakMinigameGroundScanline(u32 *pPayload0, u32 *pPayload1)
{
    StartFloorAffineHBlankDma();

    while (!(REG_DISPSTAT & 2))
        ;

    SetBgMode(1);
    REG_BG2CNT = *(const u16 *)&g_dwBuckbeakMinigameBg2Control;
}
