#include "graphics/palette.h"
#include "hw/mem.h"

void InitPaletteBuffer(PaletteBuffer *pBuffer, volatile u16 *pPaletteRam)
{
    pBuffer->pShadow = AllocZeroed(0x200);
    pBuffer->pPaletteRam = pPaletteRam;
}
