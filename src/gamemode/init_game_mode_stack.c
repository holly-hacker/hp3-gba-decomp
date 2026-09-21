#include "types.h"
#include "game_modes.h"
#include "save.h"

void InitGameModeStack(void)
{
    g_GameModeStackContext.dwCurrentGameMode = 0;
    g_dwPendingGameMode = g_GameModeStackContext;
    g_PrevGameModeCtx = g_GameModeStackContext;

    if ((g_saveManager.header.bLanguageByte & 0x80) == 0)
        PushGameMode(LanguageSelect);
    else
        PushGameMode(Startup);
}
