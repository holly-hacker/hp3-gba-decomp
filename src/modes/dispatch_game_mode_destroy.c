#include "modes.h"
#include "input.h"
#include "main.h"

void DispatchGameModeDestroy(void)
{
    void (*pDestroyFn)(void);

    ResetKeyInput();
    pDestroyFn = g_pGameModeDispatchTable[g_GameModeStackContext.dwCurrentGameMode].pDestroyFn;
    if (pDestroyFn != NULL && (g_dwGameModeFlags & GameModeFlagOverlayMode) == 0)
        pDestroyFn();
}
