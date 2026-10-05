#include "hw/input.h"

// Clears g_wInputDisabled, letting UpdateKeyInput read KEYINPUT again.
void EnableKeyInput(void)
{
    s32 i;

    g_wInputDisabled = 0;
    for (i = 0; i < ARRAY_COUNT(g_awPlayerInputDisabled_candidate); i++)
        g_awPlayerInputDisabled_candidate[i] = 0;
}
