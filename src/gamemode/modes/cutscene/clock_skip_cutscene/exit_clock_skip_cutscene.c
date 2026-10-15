#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"

void ExitClockSkipCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    UnmuteAllMusicChannels();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
