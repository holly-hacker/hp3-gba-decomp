#include "types.h"
#include "color.h"
#include "combat.h"
#include "combat_dialog.h"
#include "gen/graphics/battle.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "mem.h"

// Starts flashing the sprite of fainted ally faintedIndex between its own palette and
// gTargetFlashPalette. The palette is read at scanline 42, in HBlank.
void FlashFaintedAlly(u32 faintedIndex)
{
    Actor *actor;

    while (REG_VCOUNT != 42) {
        while (!(REG_DISPSTAT & DISPSTAT_HBLANK))
            ;
    }

    actor = g_pFightState->pFaintedAllies[faintedIndex].pActor;
    bios_CPUFastSet(&OBJ_PLTT[actor->oam.paletteNum * 16], g_aawTargetFlashPalette[0], 8);
    CopyMemory(g_aawTargetFlashPalette[1], gTargetFlashPalette, sizeof(g_aawTargetFlashPalette[1]));
    g_pFightState->nTargetFlashEffect = StartPaletteEffectWithFrameCount(
        actor->oam.paletteNum * 16, 16, 8, 0, 0x1D, g_aawTargetFlashPalette[0], 2);
}
