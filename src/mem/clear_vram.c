#include "hw/mem.h"
#include "graphics/display.h"

void ClearVram(void)
{
    memset((void *)0x06000000, 0, 0x18000);
}
