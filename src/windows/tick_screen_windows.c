#include "types.h"
#include "windows.h"

void TickScreenWindows(void)
{
    u32 i;

    for (i = 0; i < 2; i++)
        TickScreenWindow(i);
}
