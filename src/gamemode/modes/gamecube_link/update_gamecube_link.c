#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "input.h"
#include "hw/mem.h"
#include "gamecube.h"
#include "menu/gamecube_link.h"
#include "menu/in_game_menu.h"

void UpdateGameCubeLink(void)
{
    u32 linkEvent;

    linkEvent = TickJoybusSession();

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 1;
        break;

    case 1:
        if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_GameModeStackContext.dwModeSubState = 0;
            g_GameModeStackContext.dwModeState = 3;
            g_GameModeStackContext.dwCurrentGameModeArg2 = -1;
        }
        break;

    case 2:
        if (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart | KeyR | KeyL))
        {
            PlaySoundById(1);
            switch (g_GameModeStackContext.dwCurrentGameModeArg1)
            {
            case 0:
                PushGameMode(OwlNameSelect);
                break;
            case 1:
                PushGameMode(OwlCareMinigame);
                break;
            }
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            if (g_GameModeStackContext.dwCurrentGameModeArg2 == -1)
            {
                PushGameMode(g_PrevGameModeStackContext.dwCurrentGameMode);
            }
            else
            {
                switch (g_GameModeStackContext.dwCurrentGameModeArg2)
                {
                case 0:
                    break;
                case 1:
                    ClearBgTilemap(2);
                    FreeAllObjects(&g_ActiveObjectListState.pHead);
                    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
                    StartMenuOverlayFadeOut();
                    break;
                }
            }
        }
        break;
    }

    UpdateGameCubeLinkStatusText(linkEvent);
}
