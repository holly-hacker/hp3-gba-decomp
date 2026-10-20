#include "types.h"
#include "actor.h"
#include "modes.h"
#include "sound.h"
#include "pouring_minigame.h"
#include "pouring_minigame_inline.h"

void StartServePumpkinJuiceGame(void)
{
    FreeAllActors(&g_ActiveActorListState.pHead);
    SpawnServePumpkinJuiceBartender();
    SpawnServePumpkinJuiceCustomers();
    DrawServePumpkinJuiceScore();
    StopAllSoundEffects();
    g_GameModeStackContext.dwModeState = ServePumpkinJuiceStateWaitInput;
}
