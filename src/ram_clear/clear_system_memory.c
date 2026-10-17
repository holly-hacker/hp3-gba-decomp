#include "ram_clear.h"

void ClearSystemMemory(void)
{
    ClearWorkRam();
    ClearVideoMemory();
}
