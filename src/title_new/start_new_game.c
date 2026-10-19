#include "modes.h"
#include "game_state.h"
#include "title_new.h"

void StartNewGame(void)
{
    StartNewGamePlaytime();
    PushGameMode(Intro);
}
