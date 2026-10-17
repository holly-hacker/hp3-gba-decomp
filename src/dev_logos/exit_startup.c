#include "types.h"
#include "dev_logos.h"
#include "graphics/display.h"

void ExitStartup(void)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
