#include "types.h"
#include "cheat_party.h"
#include "modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateCheatParty(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_CheatPartyState.dwRow, 0, 2, 1, 0))
    {
        SetActorMoveTargetWithDuration(g_CheatPartyState.pCursorActor, 0x9C,
                                                  g_CheatPartyState.dwRow * 18 + 0x3A, 5);
    }

    if (StepCursorLeftRight(
            &g_CheatPartyState.adwCharacter[g_CheatPartyState.dwRow], 0, 9, 1, 0))
    {
        DrawCheatPartyCharacters();
    }

    if (g_wKeysPressed & (KeyA | KeyB))
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
}
