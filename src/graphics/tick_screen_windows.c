#include "types.h"
#include "graphics/display.h"

void TickScreenWindows_candidate(void)
{
    u32 i;

    for (i = 0; i < 2; i++)
        TickScreenWindow(i);
}
