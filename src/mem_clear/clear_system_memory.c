#include "mem_clear.h"

void ClearSystemMemory(void)
{
    ClearWorkRam();
    ClearVideoMemory();
}
