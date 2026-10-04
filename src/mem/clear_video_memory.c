#include "graphics/display.h"

void ClearVideoMemory(void)
{
    ClearVram();
    ClearOamDma();
    ClearPaletteRamDma();
}
