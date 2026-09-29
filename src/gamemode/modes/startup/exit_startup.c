#include "types.h"
#include "graphics/display.h"

void ExitStartup(void)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
