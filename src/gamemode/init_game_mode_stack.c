#include "types.h"
#include "game/game_modes.h"
#include "game/save.h"

void InitGameModeStack(void)
{
    g_GameModeStackContext.dwCurrentGameMode = 0;
    g_dwPendingGameMode = g_GameModeStackContext;
    g_PrevGameModeStackContext = g_GameModeStackContext;

#ifdef VERSION_JP
    PushGameMode(Startup);
#else
    if ((g_saveManager.header.bLanguageByte & 0x80) == 0)
        PushGameMode(LanguageSelect);
    else
        PushGameMode(Startup);
#endif
}
