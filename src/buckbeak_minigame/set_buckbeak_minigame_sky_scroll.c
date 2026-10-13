#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "buckbeak_minigame.h"

// Scrolls the two sky layers at different rates with the heading.
void SetBuckbeakMinigameSkyScroll(u8 heading)
{
    SetFloorHeading(heading);
    SetBgScroll(1, heading * 4, 0x20);
    SetBgScroll(0, heading * 2, 0xC0);
}
