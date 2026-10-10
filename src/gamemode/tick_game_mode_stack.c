#include "types.h"
#include "game/game_modes.h"
#include "input.h"
#include "hw/vblank.h"

void TickGameModeStack(void)
{
    TickSerialCommIfActive_candidate();
    g_dwTickCount++;

    if (IsGameModeTransitionPending())
    {
        g_dwGameModeFlags |= 0x10;
        DispatchGameModeDestroy();
        g_dwPendingGameMode.dwCurrentGameMode &= ~0x80;
        g_dwGameModeFlags &= ~0x80000000;

        g_PrevGameModeStackContext = g_GameModeStackContext;
        g_GameModeStackContext = g_dwPendingGameMode;

        DispatchGameModeInit();
        g_dwGameModeFlags &= ~0x10;
    }

    g_pVBlankState->dwFrameCounter++;
    UpdateKeyInput();
    DispatchGameModeUpdate();
    TickFrameSystems();
}
