#include "graphics.h"
#include "bios.h"

void InstallIwramDecompressCodecs(void)
{
    bios_CPUSet(DecompressLzRle, g_pDecompressLzRleIwram, 0x0400007E);
    g_pDecompressLzRleEntry = (DecompressFunc)g_pDecompressLzRleIwram;

    bios_CPUSet(DecompressGammaLz, g_pDecompressGammaLzIwram, 0x040000CF);
    g_pDecompressGammaLzEntry = (DecompressFunc)g_pDecompressGammaLzIwram;
}
