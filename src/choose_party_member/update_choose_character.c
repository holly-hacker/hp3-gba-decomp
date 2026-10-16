#include "types.h"
#include "choose_party_member.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "input.h"
#include "menu/main_menu.h"
#include "overworld/room.h"
#include "cursor.h"

void UpdateChooseCharacter(void)
{
    if (g_GameModeStackContext.dwModeTimer != 0)
    {
        g_GameModeStackContext.dwModeTimer--;
        return;
    }

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (g_abChooseCharacterTwoOptions[g_ChooseCharacterState.bStageRow] != 0)
    {
        if (StepCursorLeftRight(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 1, 1, 0))
        {
            DrawChooseCharacterSelection();
            SetMenuCursorPosition(g_ChooseCharacterState.pCursorActor,
                         g_GameModeStackContext.dwCurrentGameModeArg2 * 0x50 + 0x4D,
                         0x4E);
            PlaySoundById(0);
            return;
        }
    }
    else
    {
        if (StepCursorLeftRight(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 2, 1, 0))
        {
            DrawChooseCharacterSelection();
            SetMenuCursorPosition(g_ChooseCharacterState.pCursorActor,
                         g_GameModeStackContext.dwCurrentGameModeArg2 * 0x50 + 0x4D,
                         0x4E);
            PlaySoundById(0);
            return;
        }
    }

    if (g_ChooseCharacterState.bInputDelay != 0)
    {
        g_ChooseCharacterState.bInputDelay--;
    }
    else if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(4);
        g_dwGameModeFlags &= ~1;
        PushGameMode_2(g_PrevGameModeStackContext.dwCurrentGameMode, 9, g_bCurrentRoomId);

        g_abQuestEventState[0xFF] = g_GameModeStackContext.dwCurrentGameModeArg2;
        g_ChooseCharacterState.bPreviousStage = g_abQuestEventState[0];
        switch (g_GameModeStackContext.dwCurrentGameModeArg2)
        {
        case 0:
            g_abQuestEventState[0] = g_ChooseCharacterState.abOptionStage[0];
            break;
        case 1:
            g_abQuestEventState[0] = g_ChooseCharacterState.abOptionStage[1];
            break;
        case 2:
            g_abQuestEventState[0] = g_ChooseCharacterState.abOptionStage[2];
            break;
        }
    }
}
