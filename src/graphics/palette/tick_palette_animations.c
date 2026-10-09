#include "graphics/palette.h"
#include "graphics/display.h"

void TickPaletteAnimations_candidate(void)
{
    TickColorCycles();
    TickPaletteEffects();
}
