#include "modes.h"
#include "save.h"
#include "game_state.h"
#include "credits_cutscene.h"
#include "hero.h"
#include "main.h"
#include "map.h"

// Pushes the mode after a cutscene: the intro enters room 0x2A, the ending runs
// hippogriff, credits, replay, then the save screen with New Game+ armed. Other
// cutscenes re-enter the current room, or room 0x10 from room 5 (the baggage car).
void FinishLinearCutscene(void)
{
    if (g_GameModeStackContext.dwCurrentGameMode == Intro)
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, RoomLeakyCauldronMain);
    else if (g_GameModeStackContext.dwCurrentGameMode == HippogriffTookToAirCutscene)
        PushGameMode(Credits);
    else if (g_GameModeStackContext.dwCurrentGameMode == Credits)
        PushGameMode(GameCompletedReplayCutscene);
    else if (g_GameModeStackContext.dwCurrentGameMode == GameCompletedReplayCutscene)
    {
        ResetQuestStateForNewGame(1);
        g_saveStateBlock.bSaveFlags |= ContinueRestartsIntro;
        g_saveStateBlock.bSaveFlags |= Unknown_0x04;
        PushGameMode_2(GameSave, 0, 0);
    }
    else if (g_bCurrentRoomId == RoomHogwartsExpressBaggageCar)
    {
        g_abRoomEntryIds[0] = 0;
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, RoomEntranceHall);
        g_dwGameModeFlags |= GameModeFlagModeChangeRequested;
    }
    else
    {
        PushGameMode_3(Overworld, OverworldEntryReturn, g_bCurrentRoomId, 0xFF);
    }
}
