#include "types.h"
#include "input.h"

void ResetKeyInput(void)
{
    s32 i;

    g_wKeysHeld = 0;
    g_wKeysHeldPrevious = 0;
    g_wKeysPressed = 0;
    g_wKeysReleased = 0;

    for (i = 0; i < ARRAY_COUNT(g_awPlayerKeysHeld); i++)
    {
        g_awPlayerKeysHeld[i] = 0;
        g_awPlayerKeysHeldPrevious[i] = 0;
        g_awPlayerKeysPressed[i] = 0;
        g_awPlayerKeysReleased[i] = 0;
    }
}
