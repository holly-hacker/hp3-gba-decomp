#include "types.h"
#include "graphics/display.h"
#include "screen_transitions.h"

void ExitLanguageSelect(void)
{
    PlayScreenTransitionOutByIndex(0x3f, 2);
}
