#include "graphics.h"
#include "bios.h"

void InstallIwramDecompressCodecs(void)
{
    bios_CPUSet(DecompressType4, g_pDecompressType4Iwram, 0x0400007E);
    g_pDecompressType4Entry = (DecompressFunc)g_pDecompressType4Iwram;

    bios_CPUSet(DecompressType6, g_pDecompressType6Iwram, 0x040000CF);
    g_pDecompressType6Entry = (DecompressFunc)g_pDecompressType6Iwram;
}
