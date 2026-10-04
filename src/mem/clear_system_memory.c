#include "hw/mem.h"
#include "graphics/display.h"

void ClearSystemMemory(void)
{
    ClearWorkRam();
    ClearVideoMemory();
}
