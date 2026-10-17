#include "types.h"
#include "dev_logos.h"
#include "graphics/display.h"
#include "screen_transitions.h"

void ExitStartup(void)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
