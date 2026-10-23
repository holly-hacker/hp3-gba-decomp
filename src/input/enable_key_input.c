#include "input.h"

// Clears g_wInputDisabled, letting UpdateKeyInput read KEYINPUT again.
void EnableKeyInput(void)
{
    s32 i;

    g_wInputDisabled = 0;
    for (i = 0; i < ARRAY_COUNT(g_awInputDisabledMirror); i++)
        g_awInputDisabledMirror[i] = 0;
}
