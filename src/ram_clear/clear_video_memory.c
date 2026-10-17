#include "ram_clear.h"

void ClearVideoMemory(void)
{
    ClearVram();
    ClearOamDma();
    ClearPaletteRamDma();
}
