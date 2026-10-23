#include "input.h"

// Sets g_wInputDisabled, making UpdateKeyInput clear all key state each frame.
void DisableKeyInput(void)
{
    s32 i;

    g_wInputDisabled = 1;
    for (i = 0; i < ARRAY_COUNT(g_awInputDisabledMirror); i++)
        g_awInputDisabledMirror[i] = 1;
}
