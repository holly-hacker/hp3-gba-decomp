#include "types.h"
#include "display.h"

void ExitStartup(void)
{
    PlayScreenTransitionOutByIndex_candidate(0x3f, 2);
}
