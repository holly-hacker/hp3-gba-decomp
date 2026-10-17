#include "actor.h"
#include "sound.h"
#include "screen_transitions.h"

void ExitCheatSoundTest(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0803FF04();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
