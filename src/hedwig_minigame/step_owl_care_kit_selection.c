#include "types.h"
#include "input.h"
#include "modes.h"
#include "hedwig_minigame.h"

void StepOwlCareKitSelection(void)
{
    StepCursorLeftRight(&g_dwListMenuSelection, 0, 7, 1, 0);
}
