#include "types.h"
#include "display.h"

void ExitStartup(void)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
