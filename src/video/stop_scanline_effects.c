#include "types.h"
#include "hw/io_regs.h"
#include "video.h"

// Disables and acknowledges the VCount interrupt and clears DISPSTAT's VCOUNT
// IRQ enable and compare line.
void StopScanlineEffects(void)
{
    REG_IE &= ~4;
    REG_IF |= 4;
    REG_DISPSTAT &= 0xDF;
}
