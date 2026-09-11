#include "types.h"
#include "game_modes.h"
#include "input.h"

void DispatchGameModeDestroy(void)
{
    void (*pDestroyFn)(void);

    ResetKeyInput();
    pDestroyFn = g_pGameModeDispatchTable[g_GameModeStackContext.dwCurrentGameMode].pDestroyFn;
    if (pDestroyFn != NULL && (g_dwGameModeFlags & 1) == 0)
        pDestroyFn();
}
