#include "types.h"
#include "input.h"
#include "io_regs.h"
#include "game_modes.h"

void UpdateKeyInput(void)
{
    if (g_wInputDisabled != 0)
    {
        s32 i;

        g_wKeysHeld = 0;
        g_wKeysHeldPrevious = 0;
        g_wKeysPressed = 0;
        g_wKeysReleased = 0;

        for (i = 0; i < 2; i++)
        {
            g_awPlayerKeysHeld[i] = 0;
            g_awPlayerKeysHeldPrevious[i] = 0;
            g_awPlayerKeysPressed[i] = 0;
            g_awPlayerKeysReleased[i] = 0;
        }
        return;
    }

    if ((g_dwGameModeFlags & 0x20) != 0)
    {
        s32 i;
        s32 localPlayer = GetLocalPlayerLinkIndex_candidate();

        for (i = 0; i < 2; i++)
        {
            g_awPlayerKeysHeldPrevious[i] = g_awPlayerKeysHeld[i];
            g_awPlayerKeysHeld[i] = g_awLinkKeysReceived[i];
            g_awPlayerKeysPressed[i] = (g_awPlayerKeysHeldPrevious[i] ^ g_awPlayerKeysHeld[i]) & g_awPlayerKeysHeld[i];
            g_awPlayerKeysReleased[i] = (g_awPlayerKeysHeld[i] ^ g_awPlayerKeysHeldPrevious[i]) & g_awPlayerKeysHeldPrevious[i];
        }

        g_wKeysHeldPrevious = g_awPlayerKeysHeldPrevious[localPlayer];
        g_wKeysHeld = g_awPlayerKeysHeld[localPlayer];
    }
    else
    {
        g_wKeysHeldPrevious = g_wKeysHeld;
        g_wKeysHeld = REG_KEYINPUT ^ 0x3FF;
        g_awPlayerKeysHeldPrevious[0] = g_wKeysHeldPrevious;
        g_awPlayerKeysHeld[0] = g_wKeysHeld;
        g_awPlayerKeysPressed[0] = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeld;
        g_awPlayerKeysReleased[0] = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeldPrevious;
    }

    g_wKeysPressed = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeld;
    g_wKeysReleased = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeldPrevious;
}
