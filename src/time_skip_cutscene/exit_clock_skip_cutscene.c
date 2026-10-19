#include "sound.h"
#include "actor.h"
#include "screen_transitions.h"
#include "time_skip_cutscene.h"

void ExitClockSkipCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    StopSoundEffectChannels();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
