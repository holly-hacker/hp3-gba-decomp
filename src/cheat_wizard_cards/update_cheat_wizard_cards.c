#include "types.h"
#include "cheat_wizard_cards.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"

void UpdateCheatWizardCards(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorLeftRight(&g_CheatWizardCardsState.dwSelection, 0, 0x32, 1, 0))
        ShowCheatWizardCard();

    if (g_wKeysPressed & KeyA)
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    else if (g_wKeysPressed & KeyB)
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
