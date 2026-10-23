#include "modes.h"
#include "input.h"
#include "interrupts.h"
#include "serial.h"
#include "main.h"

void TickGameModeStack(void)
{
    TickSerialCommIfActive();
    g_dwTickCount++;

    if (IsGameModeTransitionPending())
    {
        g_dwGameModeFlags |= GameModeFlagSwitchingMode;
        DispatchGameModeDestroy();
        g_dwPendingGameMode.dwCurrentGameMode &= ~GameModeSwitchPending;
        g_dwGameModeFlags &= ~GameModeFlagModeChangeRequested;

        g_PrevGameModeStackContext = g_GameModeStackContext;
        g_GameModeStackContext = g_dwPendingGameMode;

        DispatchGameModeInit();
        g_dwGameModeFlags &= ~GameModeFlagSwitchingMode;
    }

    g_pVBlankState->dwFrameCounter++;
    UpdateKeyInput();
    DispatchGameModeUpdate();
    TickFrameSystems();
}
