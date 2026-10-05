#include "graphics/graphics.h"
#include "hw/bios.h"

void InstallBgTileCodec(void)
{
    bios_CPUSet(DecompressBgTile, g_aDecompressBgTileIwram, 0x04000040);
}
